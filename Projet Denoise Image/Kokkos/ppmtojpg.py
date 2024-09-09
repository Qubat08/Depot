from PIL import Image
import os

def convert_ppm_to_jpg(input_path, output_path):
    # Ouvrir le fichier PPM
    with Image.open(input_path) as img:
        # Convertir l'image au format JPG et sauvegarder
        img = img.convert("RGB")
        img.save(output_path, format="JPEG")
        print(f"Converted {input_path} to {output_path}")


convert_ppm_to_jpg("../res/DenoiseGaussSeidel.ppm", "../res/DenoiseGaussSeidel.jpg")
convert_ppm_to_jpg("../res/DenoiseJacobi.ppm", "../res/DenoiseJacobi.jpg")