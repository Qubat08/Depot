# JPG => PPM
from PIL import Image
import os

def convert_jpg_to_ppm(input_path, output_path):
    with Image.open(input_path) as img:
        img = img.convert("RGB")
        img.save(output_path, format="PPM")

def convert_directory(input_directory, output_directory):
    if not os.path.exists(output_directory):
        os.makedirs(output_directory)
        
    for filename in os.listdir(input_directory):
        if filename.lower().endswith(".jpg") or filename.lower().endswith(".jpeg"):
            input_path = os.path.join(input_directory, filename)
            output_path = os.path.join(output_directory, os.path.splitext(filename)[0] + ".ppm")
            convert_jpg_to_ppm(input_path, output_path)
            print(f"Converted {input_path} to {output_path}")

# Example usage:
input_directory = "../res/"
output_directory = "../res/"
convert_directory(input_directory, output_directory)
