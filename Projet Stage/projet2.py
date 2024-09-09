from PIL import Image
import matplotlib.pyplot as plt
import keras
import os
from keras.preprocessing.image import ImageDataGenerator
from keras.models import load_model, Model
from keras import backend as K
keras.backend.set_image_data_format('channels_last')
from keras.models import model_from_json
from tensorflow.keras.losses import CategoricalCrossentropy
from tensorflow.keras.optimizers import Adam
import importlib
import argparse
from tensorflow.keras.callbacks import ModelCheckpoint
from tensorflow.keras.callbacks import Callback
import math
import warnings
import tensorflow as tf
import horovod.keras as hvd
import keras
from keras import datasets, layers, models
from keras.utils import np_utils
from keras.layers import Dense, Dropout, BatchNormalization
from tensorflow.keras.utils import plot_model

import numpy as np
import time

warnings.filterwarnings('always')

# Ajoutez la fonction de chargement des données
def load_data(data_dir):
    # Chargement des fichiers sauvegardés
    x_train = np.load(os.path.join(data_dir, 'x_train.npy'))
    y_train = np.load(os.path.join(data_dir, 'y_train.npy'))
    x_test = np.load(os.path.join(data_dir, 'x_test.npy'))
    y_test = np.load(os.path.join(data_dir, 'y_test.npy'))

    return (x_train, y_train), (x_test, y_test)

# Fonction d'importation dynamique de fonction
def import_function(module_name, function_name):
    module = importlib.import_module(module_name)
    function = getattr(module, function_name)
    return function

def arg_parser():
    parser = argparse.ArgumentParser(description='Process some integers.')
    parser.add_argument('--data_train', type=str, help='data_train repo')
    parser.add_argument('--data_test', type=str, help='data_test repo')
    parser.add_argument('--module_name', type=str, help='module name')
    parser.add_argument('--function_name', type=str, help='function name')
    parser.add_argument('--gpu', type=str, help='gpu')
    parser.add_argument('--epoch', type=int, help='epochs', default=10)
    parser.add_argument('--batch', type=int, help='batch', default=8)
    parser.add_argument('--data', type=str, help='batch')
    parser.add_argument('--num_classes', type=int, help='Num Classes')
    return parser.parse_args()

# Horovod: initialize Horovod.
hvd.init()

args = arg_parser()
# Horovod: pin GPU to be used to process local rank (one GPU per process)
print(f'Rank: {hvd.rank()}, Local Rank: {hvd.local_rank()}, Size: {hvd.size()}')

# Obtenez le rang local (indice de GPU local pour chaque processus)
local_rank = hvd.local_rank()

# Définir CUDA_VISIBLE_DEVICES pour restreindre la visibilité à un seul GPU
os.environ["CUDA_VISIBLE_DEVICES"] = str(local_rank)
print(f'CUDA_VISIBLE_DEVICES: {os.environ["CUDA_VISIBLE_DEVICES"]}')

# Liste des GPUs restreinte à un seul GPU visible
gpus = tf.config.experimental.list_physical_devices('GPU')

if gpus:
    try:
        # Empêche TensorFlow de pré-allouer toute la mémoire GPU
        for gpu in gpus:
            tf.config.experimental.set_memory_growth(gpu, True)
        # Assigner le GPU visible à TensorFlow
        tf.config.experimental.set_visible_devices(gpus[0], 'GPU')
    except RuntimeError as e:
        print(e)


# Taille de batch
gpu = int(args.gpu)
Batch = int(args.batch)
BS = gpu * Batch

seed = 1

# Horovod: adjust number of epochs based on number of GPUs.
epochs = int(math.ceil(args.epoch / int(args.gpu)))

# Chargement des données CIFAR-10 sauvegardées
data_directory = args.data

if data_directory == "cifar10_data" or data_directory == "cifar100_data":
    # load Cifar data
    print("Load CIFAR10")
    (x_train, y_train), (x_test, y_test) = load_data(data_directory)

    x_train = x_train.astype('float32') / 255.0
    x_test = x_test.astype('float32') / 255.0

    y_train = np_utils.to_categorical(y_train, args.num_classes)
    y_test = np_utils.to_categorical(y_test, args.num_classes)
    
    train_datagen = ImageDataGenerator(
        horizontal_flip=False,
        vertical_flip=False)

    val_datagen = ImageDataGenerator(
        horizontal_flip=False,
        vertical_flip=False)

    train_generator = train_datagen.flow(
        x_train, y_train,
        batch_size=BS)

    val_generator = val_datagen.flow(
        x_test, y_test,
        batch_size=BS)

    NO_OF_TRAINING_IMAGES = x_train.shape[0]
    NO_OF_VAL_IMAGES = x_test.shape[0]

elif data_directory == "imagenette2":
    # Load Imagenette2 dataset
    train_data_dir = os.path.join(data_directory, 'train')
    val_data_dir = os.path.join(data_directory, 'val')
    train_datagen = ImageDataGenerator(
        rescale=1./255,
        horizontal_flip=False,
        vertical_flip=False)

    val_datagen = ImageDataGenerator(
        rescale=1./255,
        horizontal_flip=False,
        vertical_flip=False)

    train_generator = train_datagen.flow_from_directory(
        train_data_dir,
        target_size=(224, 224),  # assuming you want to resize images to 224x224
        batch_size=BS,
        class_mode='categorical')

    val_generator = val_datagen.flow_from_directory(
        val_data_dir,
        target_size=(224, 224),  # assuming you want to resize images to 224x224
        batch_size=BS,
        class_mode='categorical')

    NO_OF_TRAINING_IMAGES = train_generator.samples
    NO_OF_VAL_IMAGES = val_generator.samples

# Créez ou chargez le modèle
if (args.module_name != "None" and args.function_name != "None" and args.function_name != "json"):
    my_func = import_function(args.module_name, args.function_name)
    model = my_func()
elif (isinstance(args.module_name, str) and args.function_name == "json"):
    # load from Json
    print("LOAD FROM JSON")
    json_file = open('%s.json' % args.module_name, 'r')
    modelRead = json_file.read()
    json_file.close()
    modelLoad = model_from_json(modelRead)

    modelLoad.load_weights("%s.h5" % args.module_name)
    print("Arg model none : Loaded model from disk")
    model = modelLoad
elif (isinstance(args.module_name, str) and args.function_name == "None"):
    # load from h5 file
    print("LOAD FROM H5")
    model = load_model("%s.h5" % args.module_name)

# Créez l'optimizer
optimizer = hvd.DistributedOptimizer(Adam())

# Compilez le modèle
model.compile(optimizer=optimizer, 
              loss=CategoricalCrossentropy(), 
              metrics=['accuracy'])


# Calculer les steps par epoch et les steps de validation
step_epochs = math.ceil(NO_OF_TRAINING_IMAGES / BS)
step_val = math.ceil(NO_OF_VAL_IMAGES / BS)

# Callbacks
callbacks = [
    hvd.callbacks.BroadcastGlobalVariablesCallback(0),
    hvd.callbacks.MetricAverageCallback(),
]

# if hvd.rank() == 0:
#     callbacks.append(keras.callbacks.ModelCheckpoint(
#         filepath='./checkpoint-best-{epoch}.h5',  
#         monitor='val_accuracy', 
#         mode='max',
#         save_best_only=True,
#         verbose=1
#     ))

# Afficher la mémoire requise par le modèle
def get_model_memory_usage(batch_size, model):
    import numpy as np
    from keras import backend as K

    shapes_mem_count = 0
    for layer in model.layers:
        output_shape = layer.output_shape
        if isinstance(output_shape, tuple): 
            if None in output_shape:  
                output_shape = tuple(batch_size if s is None else s for s in output_shape)
        elif isinstance(output_shape, list): 
            output_shape = [tuple(batch_size if s is None else s for s in shape) for shape in output_shape]

        if isinstance(output_shape, list): 
            layer_mem = sum(np.prod(shape) for shape in output_shape)
        else: 
            layer_mem = np.prod(output_shape)

        shapes_mem_count += layer_mem

    trainable_count = np.sum([K.count_params(p) for p in model.trainable_weights])
    non_trainable_count = np.sum([K.count_params(p) for p in model.non_trainable_weights])

    number_size = np.dtype(K.floatx()).itemsize

    total_memory = number_size * (batch_size * shapes_mem_count + trainable_count + non_trainable_count)
    gbytes = np.round(total_memory / (1024.0 ** 3), 3)  # Conversion en gigaoctets
    return gbytes

print("Mémoire requise par le modèle pour un batch size de "+str(BS)+" : "+
      str(get_model_memory_usage(BS, model))+" go")

# Entraînement du modèle
start_time = time.time()
results = model.fit(
    train_generator, 
    epochs=epochs, 
    steps_per_epoch=step_epochs,
    validation_data=val_generator, 
    validation_steps=step_val,
    callbacks=callbacks
)
end_time = time.time()
training_duration = (end_time - start_time) / 60  # Convert seconds to minutes
print(f"Training time: {training_duration:.2f} minutes")

# Évaluation du modèle
if data_directory in ["cifar10_data", "cifar100_data"]:
    test_loss, test_accuracy = model.evaluate(x_test, y_test, verbose=2)
elif data_directory == "imagenette2":
    test_loss, test_accuracy = model.evaluate(val_generator, steps=math.ceil(NO_OF_VAL_IMAGES / BS), verbose=2)

# Réduction des métriques de test
test_loss = hvd.allreduce(test_loss)
test_accuracy = hvd.allreduce(test_accuracy)

if hvd.rank() == 0:
    print(f"Test Loss: {test_loss}")
    print(f"Test Accuracy: {test_accuracy}")

    # Graphiques des résultats
    train_loss = results.history['loss']
    train_accuracy = results.history['accuracy']
    val_loss = results.history['val_loss']
    val_accuracy = results.history['val_accuracy']
    epochs_range = range(1, len(train_loss) + 1)

    plt.figure()
    plt.plot(epochs_range, train_loss, 'b', label='Training Loss')
    plt.plot(epochs_range, val_loss, 'g', label='Validation Loss')
    plt.title('Training and Validation Loss')
    plt.xlabel('Epochs')
    plt.ylabel('Loss')
    plt.legend()
    plt.savefig('training_validation_loss.png')

    plt.figure()
    plt.plot(epochs_range, train_accuracy, 'r', label='Training Accuracy')
    plt.plot(epochs_range, val_accuracy, 'm', label='Validation Accuracy')
    plt.title('Training and Validation Accuracy')
    plt.xlabel('Epochs')
    plt.ylabel('Accuracy')
    plt.legend()
    plt.savefig('training_validation_accuracy.png')
