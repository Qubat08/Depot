#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <chrono>
#include <omp.h>

using namespace std;

#define DENOISE_ITER 15

struct Pixel {
    unsigned char r, g, b;
};

struct Image {
    int width, height;
    Pixel* pixels;

    Image(int w = 0, int h = 0) : width(w), height(h), pixels(nullptr) {
        if (w > 0 && h > 0)
            pixels = new Pixel[w * h];
    }

    ~Image() {
        delete[] pixels;
    }

    Image(const Image& other) : width(other.width), height(other.height) {
        pixels = new Pixel[width * height];
        std::copy(other.pixels, other.pixels + width * height, pixels);
    }

    Image& operator=(const Image& other) {
        if (this != &other) {
            delete[] pixels;
            width = other.width;
            height = other.height;
            pixels = new Pixel[width * height];
            std::copy(other.pixels, other.pixels + width * height, pixels);
        }
        return *this;
    }

    Pixel& at(int i, int j) {
        return pixels[i * width + j];
    }

    const Pixel& at(int i, int j) const {
        return pixels[i * width + j];
    }
};

Image readPPM(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Could not open file");
    }

    std::string header;
    file >> header;
    if (header != "P6") {
        throw std::runtime_error("Invalid PPM file");
    }

    int width, height, maxVal;
    file >> width >> height >> maxVal;
    file.ignore(256, '\n'); // Skip to the binary data

    Image img(width, height);

    file.read(reinterpret_cast<char*>(img.pixels), width * height * 3);

    return img;
}

void writePPM(const std::string &filename, const Image &img) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Could not open file to write");
    }

    file << "P6\n" << img.width << " " << img.height << "\n255\n";
    file.write(reinterpret_cast<const char*>(img.pixels), img.width * img.height * 3);
}

void jacobiDenoise(const Image &input, Image &output, int iterations) {
    output = input;
    Image temp = input;

    int width = input.width;
    int height = input.height;

    for (int iter = 0; iter < iterations; iter++) {
        #pragma omp parallel
        {
            #pragma omp single
            {
                for (int i = 0; i < height; i++) {
                    #pragma omp task firstprivate(i)
                    {
                        #pragma omp target teams distribute parallel for map(to: temp.pixels[0:width * height]) map(tofrom: output.pixels[0:width * height]) firstprivate(width, height, i)
                        for (int j = 0; j < width; j++) {
                            int sumR = 0, sumG = 0, sumB = 0;
                            int count = 0;

                            if (i > 0) {
                                sumR += temp.pixels[(i - 1) * width + j].r;
                                sumG += temp.pixels[(i - 1) * width + j].g;
                                sumB += temp.pixels[(i - 1) * width + j].b;
                                count++;
                            }
                            if (i < height - 1) {
                                sumR += temp.pixels[(i + 1) * width + j].r;
                                sumG += temp.pixels[(i + 1) * width + j].g;
                                sumB += temp.pixels[(i + 1) * width + j].b;
                                count++;
                            }
                            if (j > 0) {
                                sumR += temp.pixels[i * width + (j - 1)].r;
                                sumG += temp.pixels[i * width + (j - 1)].g;
                                sumB += temp.pixels[i * width + (j - 1)].b;
                                count++;
                            }
                            if (j < width - 1) {
                                sumR += temp.pixels[i * width + (j + 1)].r;
                                sumG += temp.pixels[i * width + (j + 1)].g;
                                sumB += temp.pixels[i * width + (j + 1)].b;
                                count++;
                            }
                            sumR += temp.pixels[i * width + j].r;
                            sumG += temp.pixels[i * width + j].g;
                            sumB += temp.pixels[i * width + j].b;
                            count++;

                            output.pixels[i * width + j].r = static_cast<unsigned char>(sumR / count);
                            output.pixels[i * width + j].g = static_cast<unsigned char>(sumG / count);
                            output.pixels[i * width + j].b = static_cast<unsigned char>(sumB / count);
                        }
                    }
                }
            }
        }
        #pragma omp taskwait
        temp = output;
    }
}

void gaussSeidelDenoiseWavefront(const Image &input, Image &output, int iterations) {
    output = input;
    Image temp = input;

    int width = input.width;
    int height = input.height;

    for (int iter = 0; iter < iterations; iter++) {
        #pragma omp parallel
        {
            #pragma omp single
            {
                for (int front = 0; front < height + width - 1; front++) {
                    #pragma omp task firstprivate(front)
                    {
                        #pragma omp target teams distribute parallel for map(to: temp.pixels[0:width * height]) map(tofrom: output.pixels[0:width * height]) firstprivate(width, height, front)
                        for (int i = 0; i < height; i++) {
                            int j = front - i;
                            if (j >= 0 && j < width) {
                                int sumR = 0, sumG = 0, sumB = 0;
                                int count = 0;

                                if (i > 0) {
                                    sumR += output.pixels[(i - 1) * width + j].r;
                                    sumG += output.pixels[(i - 1) * width + j].g;
                                    sumB += output.pixels[(i - 1) * width + j].b;
                                    count++;
                                }
                                if (j > 0) {
                                    sumR += output.pixels[i * width + (j - 1)].r;
                                    sumG += output.pixels[i * width + (j - 1)].g;
                                    sumB += output.pixels[i * width + (j - 1)].b;
                                    count++;
                                }
                                if (i < height - 1) {
                                    sumR += temp.pixels[(i + 1) * width + j].r;
                                    sumG += temp.pixels[(i + 1) * width + j].g;
                                    sumB += temp.pixels[(i + 1) * width + j].b;
                                    count++;
                                }
                                if (j < width - 1) {
                                    sumR += temp.pixels[i * width + (j + 1)].r;
                                    sumG += temp.pixels[i * width + (j + 1)].g;
                                    sumB += temp.pixels[i * width + (j + 1)].b;
                                    count++;
                                }

                                sumR += temp.pixels[i * width + j].r;
                                sumG += temp.pixels[i * width + j].g;
                                sumB += temp.pixels[i * width + j].b;
                                count++;

                                output.pixels[i * width + j].r = static_cast<unsigned char>(sumR / count);
                                output.pixels[i * width + j].g = static_cast<unsigned char>(sumG / count);
                                output.pixels[i * width + j].b = static_cast<unsigned char>(sumB / count);
                            }
                        }
                    }
                }
            }
        }
        #pragma omp taskwait
        temp = output;
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <Input_image>" << std::endl;
        return -1;
    }

    Image input;
    try {
        input = readPPM(argv[1]);
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        return -1;
    }

    int iterations = DENOISE_ITER;

    {
        Image Jacobioutput(input.width, input.height);
        auto start = std::chrono::high_resolution_clock::now();
        jacobiDenoise(input, Jacobioutput, iterations);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "jacobiDenoise elapsed time: " << elapsed_seconds.count() << "s\n";

        writePPM("res/DenoiseJacobi.ppm", Jacobioutput);
    }

    {
        Image GaussSeideloutput(input.width, input.height);
        auto start = std::chrono::high_resolution_clock::now();
        gaussSeidelDenoiseWavefront(input, GaussSeideloutput, iterations);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "gaussSeidelDenoise elapsed time: " << elapsed_seconds.count() << "s\n";

        writePPM("res/DenoiseGaussSeidel.ppm", GaussSeideloutput);
    }

    return 0;
}
