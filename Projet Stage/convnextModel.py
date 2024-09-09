import tensorflow as tf
from tensorflow.keras import layers, models

# Définition de LayerScale, une couche personnalisée utilisée dans ConvNeXt
class LayerScale(layers.Layer):
    def __init__(self, init_value=1e-6, **kwargs):
        super().__init__(**kwargs)
        self.init_value = init_value

    def build(self, input_shape):
        self.gamma = self.add_weight(
            shape=(input_shape[-1],),
            initializer=tf.keras.initializers.Constant(self.init_value),
            trainable=True,
            name="gamma"
        )

    def call(self, inputs):
        return inputs * self.gamma

# Blocs ConvNeXt
def convnext_block(x, filters, layer_scale_init_value=1e-6):
    shortcut = x

    # Depthwise Convolution
    x = layers.DepthwiseConv2D(kernel_size=7, padding='same')(x)
    x = layers.LayerNormalization(epsilon=1e-6)(x)

    # Pointwise Convolution 1
    x = layers.Dense(4 * filters)(x)
    x = layers.Activation('gelu')(x)

    # Pointwise Convolution 2
    x = layers.Dense(filters)(x)
    
    # Layer Scale
    x = LayerScale(init_value=layer_scale_init_value)(x)

    # Residual connection
    x = layers.Add()([shortcut, x])

    return x

# Modèle ConvNeXt
def createModel(input_shape=(224, 224, 3), num_classes=10):
    inputs = layers.Input(shape=input_shape)

    # Initial Stem
    x = layers.Conv2D(96, kernel_size=4, strides=4)(inputs)
    x = layers.LayerNormalization(epsilon=1e-6)(x)

    # Stage 1
    for _ in range(3):
        x = convnext_block(x, filters=96)
    x = layers.Conv2D(192, kernel_size=2, strides=2)(x)  # Downsampling

    # Stage 2
    for _ in range(3):
        x = convnext_block(x, filters=192)
    x = layers.Conv2D(384, kernel_size=2, strides=2)(x)  # Downsampling

    # Stage 3
    for _ in range(9):
        x = convnext_block(x, filters=384)
    x = layers.Conv2D(768, kernel_size=2, strides=2)(x)  # Downsampling

    # Stage 4
    for _ in range(3):
        x = convnext_block(x, filters=768)

    # Classification Head
    x = layers.GlobalAveragePooling2D()(x)
    x = layers.LayerNormalization(epsilon=1e-6)(x)
    x = layers.Dense(num_classes, activation='softmax')(x)

    # Create model
    model = models.Model(inputs, x)
    
    # Compile the model

    return model