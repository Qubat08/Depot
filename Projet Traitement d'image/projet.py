import sys
import numpy as np
from imageio.v3 import imread, imwrite
from scipy.ndimage import convolve
import matplotlib.pyplot as plt
import os

def calculate_energy_map(image):
    filter_du = np.array([[1.0, 2.0, 1.0],[0.0, 0.0, 0.0],[-1.0, -2.0, -1.0],])
    filter_du = np.stack([filter_du] * 3, axis=2)
    filter_dv = np.array([[1.0, 0.0, -1.0],[2.0, 0.0, -2.0],[1.0, 0.0, -1.0],])
    filter_dv = np.stack([filter_dv] * 3, axis=2)

    img = image.astype('float32')
    convolved = np.absolute(convolve(img, filter_du)) + np.absolute(convolve(img, filter_dv))

    energy_map = convolved.sum(axis=2)

    return energy_map


def minimum_seam(image):
    
    if len(image.shape) == 3:
        length, width, _ = image.shape
    else:
        length, width = image.shape

    energy_map = calculate_energy_map(image)
    M = energy_map.copy()
    backtrack = np.zeros_like(M, dtype=int)
    for i in range(1, length):
        for j in range(0, width):
            if j == 0:
                idx = np.argmin(M[i - 1, j:j + 2])
                backtrack[i, j] = idx + j
                min_energy = M[i - 1, idx + j]
            else:
                idx = np.argmin(M[i - 1, j - 1:j + 2])
                backtrack[i, j] = idx + j - 1
                min_energy = M[i - 1, idx + j - 1]

            M[i, j] += min_energy

    return M, backtrack


def carve_column(image, marked_image):
    if len(image.shape) == 3:
        length, width, num_channels = image.shape
    else:
        length, width = image.shape
        num_channels = 1

    M, backtrack = minimum_seam(image)

    mask = np.ones((length, width), dtype=bool)

    j = np.argmin(M[-1])

    for i in reversed(range(length)):
        mask[i, j] = False
        if num_channels == 3:
            marked_image[i, j, :] = [255, 0, 0]
        elif num_channels == 4:
            marked_image[i, j, :] = [255, 0, 0, 255]
        else:
            marked_image[i, j] = 255

        j = backtrack[i, j]

    if num_channels == 1:
        image = image[mask].reshape((length, width - 1))
    else:
        mask = np.stack([mask] * num_channels, axis=2)
        image = image[mask].reshape((length, width - 1, num_channels))

    return image, marked_image

def crop_column(img, scale, boolAffichage):

    if len(img.shape) == 3:
        length, width, _ = img.shape
    else:
        length, width = img.shape

    new_scale = int(scale * width)

    # Create a copy of the image to mark deleted pixels
    marked_image = img.copy()

    for i in range(width - new_scale):
        img, marked_image = carve_column(img, marked_image)
        if (boolAffichage):
            print("Etape: ", i + 1, "/", width - new_scale)
            img_shape = np.shape(img)
            print("Width: ", img_shape[1])

    return img, marked_image

def main():
    if len(sys.argv) > 3:
        name_image_in = sys.argv[1]
        scale = float(sys.argv[2])
        bool_affichage = bool(sys.argv[3])
       
    else:
        name_image_in = "castlemin.png"
        scale = 0.8
        bool_affichage = False
    
    path = os.getcwd() + "/data/"
    name_image_out = 'ImageOutProjet.png'
    name_marked_image_out = 'MarkedImageOutProjet.png'
    name_chaleur_image_out = 'ChaleurImage.png'
    image = imread(path + name_image_in)
    matrix = np.array(image)

    if len(matrix.shape) < 3:
        matrix = np.expand_dims(matrix, axis=2)

    # Calculer la carte d'énergie en utilisant le type spécifié
    energy_map = calculate_energy_map(matrix)
   
    # Exécuter le calcul du seam carving
    out, marked_image = crop_column(matrix, scale, bool_affichage)
    show_energy_map(matrix, energy_map)

    imwrite(path + name_image_out, out)
    imwrite(path + name_marked_image_out, marked_image)
    plt.figure(figsize=(15, 5))

    plt.subplot(1, 3, 1)
    plt.imshow(image, cmap='gray')
    plt.title('Image Originale')

    plt.subplot(1, 3, 2)
    plt.imshow(marked_image, cmap='gray')
    plt.title('Image marquée')

    plt.subplot(1, 3, 3)
    plt.imshow(out, cmap='gray')
    plt.title('Image finale')

    plt.show()


def show_energy_map(image, energy_map):
    plt.figure(figsize=(10, 5))

    plt.subplot(1, 2, 1)
    plt.imshow(image, cmap='gray')
    plt.title('Image Originale')

    plt.subplot(1, 2, 2)
    plt.imshow(energy_map, cmap='viridis')
    plt.title('Carte d\'Énergie')

    # Afficher la fenêtre de la carte d'énergie
    plt.show()

if __name__ == '__main__':   
    main()
