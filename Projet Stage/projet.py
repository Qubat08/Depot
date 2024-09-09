from PIL import Image
import matplotlib.pyplot as plt
import keras
import os
from keras.preprocessing.image import ImageDataGenerator
from keras.models import load_model, Model
from keras.models import Sequential
from keras import backend as K
keras.backend.set_image_data_format('channels_last')
from keras.models import model_from_json
from tensorflow.keras.losses import CategoricalCrossentropy
from tensorflow.keras.optimizers import Adam
import importlib
import argparse

import warnings
warnings.filterwarnings('always') 

# commande load from script execution: 
    #  horovodrun -np 1 python3 projet.py cifar10/train/ cifar10/test/ model createModel 4 10 8

# commande load from h5 execution:
    #  horovodrun -np 1 python3 projet.py cifar10/train/ cifar10/test/ checkpoint-best None 4 10 8
    
# commande load from json execution:
    #  horovodrun -np 1 python3 projet.py cifar10/train/ cifar10/test/ cifar10_model json 4 10 8

#Fonction d'affichage des images couleur ou niveau de gris
def showImg(img):
    img = cv2.cvtColor(img,cv2.COLOR_BGR2RGB)
    plt.imshow(img)
    plt.show()
    
def showNDG(img):
    plt.imshow(img,'gray')
    plt.show()

def import_function(module_name, function_name):
    module = importlib.import_module(module_name)
    function = getattr(module, function_name)
    return function

def arg_parser():
    parser = argparse.ArgumentParser(description='Process some integers.')
    parser.add_argument('data_train', type=str, help='data_train repo')
    parser.add_argument('data_test', type=str, help='data_test repo')
    parser.add_argument('module_name', type=str, help='module name')
    parser.add_argument('function_name', type=str, help='function name')
    parser.add_argument('gpu', type=str, help='gpu')
    parser.add_argument('epoch', type=str, help='epochs', default="10")
    parser.add_argument('batch', type=str, help='batch', default="8")
    return parser.parse_args()

import math
import tensorflow as tf
import horovod.keras as hvd
# Horovod: initialize Horovod.
hvd.init()


args = arg_parser()


if (args.module_name != "None" and args.function_name != "None" and args.function_name != "json"):
    my_func = import_function(args.module_name, args.function_name)
    model = my_func()


# Horovod: pin GPU to be used to process local rank (one GPU per process)
gpus = tf.config.experimental.list_physical_devices('GPU')
if gpus:
    try:
        for gpu in gpus:
            tf.config.experimental.set_memory_growth(gpu, True)
        tf.config.experimental.set_visible_devices(gpus[hvd.local_rank()], 'GPU')
    except RuntimeError as e:
        print(e)

# print("Taille %d" %hvd.size())
# print(gpus)


# Horovod: adjust number of epochs based on number of GPUs.
epochs = int(math.ceil(int(args.epoch) / hvd.size()))

if(hvd.size()==8):
    epochs = int(math.ceil(int(args.epoch) / hvd.size()))+5

#Modèle pré-entrainé sur imagenet
# BACKBONE = 'inceptionv3'

#preprocess_input = get_preprocessing(BACKBONE)

#Dossier contenant les données d'apprentissage et de validation
dir_train_frames = args.data_train
dir_val_frames = args.data_train

#Taille des blocs
patch_size = (224,224)

#Taille de batch
#BS = 32
gpu= int(args.gpu)
Batch = int(args.batch)
BS = gpu * Batch

seed = 1

#Initialisation des générateurs de données
#rescale: convertie les pixels Int(0-255) vers float (0.0-1.0)
gen = ImageDataGenerator(rescale=1./255.0)
val_datagen = ImageDataGenerator(rescale=1./255.0)

#Pour tester la génération de données artificielles
gen = ImageDataGenerator(rescale=1./255, horizontal_flip=True, vertical_flip=True)
val_datagen = ImageDataGenerator(rescale=1./255, horizontal_flip=True, vertical_flip=True)

train_generator = gen.flow_from_directory(
    dir_train_frames,
    target_size=(32, 32), 
    class_mode='categorical',
    batch_size=BS,
    seed=seed)

val_generator = val_datagen.flow_from_directory(
    dir_val_frames,
    target_size=(32, 32), 
    class_mode='categorical',
    batch_size=BS,
    seed=seed)


#Création des générateurs de données pour l'apprentissage et la validation
# train_generator = zip(train_image_generator)
# val_generator = zip(val_image_generator)

#Nombre d'images
NO_OF_TRAINING_IMAGES = len(os.listdir(dir_train_frames))
NO_OF_VAL_IMAGES = len(os.listdir(dir_val_frames))
# print(NO_OF_TRAINING_IMAGES)
# print(NO_OF_VAL_IMAGES)

if (isinstance(args.module_name, str) and args.function_name == "json"):
    # load from Json
    print("LOAD FROM JSON")
    json_file = open('%s.json'% args.module_name, 'r')
    modelRead = json_file.read()
    json_file.close()
    modelLoad = model_from_json(modelRead)

    modelLoad.load_weights("%s.h5"% args.module_name)
    print("Arg model none : Loaded model from disk")
    model = modelLoad

elif (isinstance(args.module_name, str) and args.function_name == "None"):
    # load from h5 file
    print("LOAD FROM H5")
    model = load_model("%s.h5" %args.module_name)

# model.summary()

#Création du modèle
#Architecture Unet de type Encodeur-Décodeur
#Encodeur initialisé avec les paramètres de VGG-16 entrainé sur ImageNet
#m = Unet(BACKBONE, encoder_weights='imagenet',input_shape=(patch_size[0],patch_size[1],3))
#Créez votre modèle ici
#Vous pouvez utiliser le package si vous travaillez sur votre machine: https://github.com/qubvel/segmentation_models

# Horovod: adjust learning rate based on number of GPUs.
opt = Adam(learning_rate=0.001 * hvd.size())

# Horovod: add Horovod Distributed Optimizer.
opt = hvd.DistributedOptimizer(opt)

loss_function = CategoricalCrossentropy()

callbacks = [
    hvd.callbacks.BroadcastGlobalVariablesCallback(0),
]

if hvd.rank() == 0:
    callbacks.append(keras.callbacks.ModelCheckpoint(
        filepath='./checkpoint-best.h5',  
        monitor='val_accuracy', 
        mode='max',
        save_best_only=True,
        verbose=0
    ))
  

    
def get_model_memory_usage(batch_size, model):
    import numpy as np
    from keras import backend as K

    shapes_mem_count = 0
    for layer in model.layers:
        # On obtient la forme de sortie de la couche et on remplace les None par la taille du batch
        output_shape = layer.output_shape
        if isinstance(output_shape, tuple): 
            if None in output_shape:  
                output_shape = tuple(batch_size if s is None else s for s in output_shape)
        elif isinstance(output_shape, list): 
            output_shape = [tuple(batch_size if s is None else s for s in shape) for shape in output_shape]

        # Calcul de la mémoire nécessaire pour chaque forme de sortie
        if isinstance(output_shape, list): 
            layer_mem = sum(np.prod(shape) for shape in output_shape)
        else: 
            layer_mem = np.prod(output_shape)

        shapes_mem_count += layer_mem

    # Calcul des paramètres entraînables et non entraînables
    trainable_count = np.sum([K.count_params(p) for p in model.trainable_weights])
    non_trainable_count = np.sum([K.count_params(p) for p in model.non_trainable_weights])


    number_size = np.dtype(K.floatx()).itemsize

    total_memory = number_size * (batch_size * shapes_mem_count + trainable_count + non_trainable_count)
    gbytes = np.round(total_memory / (1024.0 ** 3), 3)  # Conversion en gigaoctets
    return gbytes


print("Mémoire requise par le modèle pour un batch size de "+str(BS)+" : "+
      str(get_model_memory_usage(BS,model))+" go")


#Création de l'optimizer(ie descente de gradient)
#compilation du modèle
opti = opt
model.compile(opti, loss=loss_function, metrics=['accuracy'])

# model.summary()

#checkpoint = ModelCheckpoint(weights_path, monitor='loss', verbose=1, save_best_only=True)
#csv_logger = CSVLogger('log.out', append=True, separator=';')
#earlystopping = EarlyStopping(monitor = 'val_loss', verbose = 1,min_delta = 0.01, patience = 3, mode = 'max')
#callbacks_list = [checkpoint, csv_logger] #earlystopping]

import math
step_epochs = math.ceil(NO_OF_TRAINING_IMAGES/BS)
step_val = math.ceil(NO_OF_VAL_IMAGES/BS)

#Apprentissage
results = model.fit(
    train_generator, 
    epochs=epochs, 
    steps_per_epoch = step_epochs,
    validation_data=val_generator, 
    validation_steps=step_val,
    callbacks=callbacks)

