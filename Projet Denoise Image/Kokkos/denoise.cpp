#include <iostream>
#include <chrono>
#include <Kokkos_Core.hpp>
#include <fstream>
#include <vector>

#define DENOISE_ITER 15

struct Pixel {
    unsigned char r, g, b;
};

struct Image {
    int width, height;
    Kokkos::View<Pixel**> pixels;
};

// Function to read a PPM file
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

    Image img;
    file >> img.width >> img.height;

    int maxVal;
    file >> maxVal;
    file.ignore(256, '\n'); // Skip to the binary data

    img.pixels = Kokkos::View<Pixel**>("pixels", img.height, img.width);

    auto pixels_mirror = Kokkos::create_mirror_view(img.pixels);
    for (int i = 0; i < img.height; ++i) {
        for (int j = 0; j < img.width; ++j) {
            file.read(reinterpret_cast<char*>(&pixels_mirror(i, j)), 3);
        }
    }
    Kokkos::deep_copy(img.pixels, pixels_mirror);

    return img;
}

// Function to write a PPM file
void writePPM(const std::string &filename, const Image &img) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Could not open file to write");
    }

    file << "P6\n" << img.width << " " << img.height << "\n255\n";

    auto pixels_mirror = Kokkos::create_mirror_view(img.pixels);
    Kokkos::deep_copy(pixels_mirror, img.pixels);

    for (int i = 0; i < img.height; ++i) {
        for (int j = 0; j < img.width; ++j) {
            file.write(reinterpret_cast<const char*>(&pixels_mirror(i, j)), 3);
        }
    }
}

void jacobiDenoise(const Image &input, Image &output, int iterations) {
    output = input;
    Image temp = input;

    for (int iter = 0; iter < iterations; iter++) {
        Kokkos::parallel_for("JacobiDenoise", Kokkos::MDRangePolicy<Kokkos::Rank<2>>({0, 0}, {input.height, input.width}),
                             KOKKOS_LAMBDA(const int i, const int j) {
            int sumR = 0, sumG = 0, sumB = 0;
            int count = 0;

            if (i > 0) {
                sumR += temp.pixels(i - 1, j).r;
                sumG += temp.pixels(i - 1, j).g;
                sumB += temp.pixels(i - 1, j).b;
                count++;
            }
            if (i < input.height - 1) {
                sumR += temp.pixels(i + 1, j).r;
                sumG += temp.pixels(i + 1, j).g;
                sumB += temp.pixels(i + 1, j).b;
                count++;
            }
            if (j > 0) {
                sumR += temp.pixels(i, j - 1).r;
                sumG += temp.pixels(i, j - 1).g;
                sumB += temp.pixels(i, j - 1).b;
                count++;
            }
            if (j < input.width - 1) {
                sumR += temp.pixels(i, j + 1).r;
                sumG += temp.pixels(i, j + 1).g;
                sumB += temp.pixels(i, j + 1).b;
                count++;
            }
            sumR += temp.pixels(i, j).r;
            sumG += temp.pixels(i, j).g;
            sumB += temp.pixels(i, j).b;
            count++;

            output.pixels(i, j).r = static_cast<unsigned char>(sumR / 5);
            output.pixels(i, j).g = static_cast<unsigned char>(sumG / 5);
            output.pixels(i, j).b = static_cast<unsigned char>(sumB / 5);
        });

        Kokkos::deep_copy(temp.pixels, output.pixels);
    }
}

void gaussSeidelDenoiseWavefront(const Image &input, Image &output, int iterations) {
    output = input;
    Image temp = input;

    for (int iter = 0; iter < iterations; iter++) {
        Kokkos::parallel_for("GaussSeidelDenoiseWavefront", Kokkos::MDRangePolicy<Kokkos::Rank<2>>({0, 0}, {input.height, input.width}),
                             KOKKOS_LAMBDA(const int i, const int j) {
            int sumR = 0, sumG = 0, sumB = 0;
            int count = 0;

            if (i > 0) {
                sumR += output.pixels(i - 1, j).r;
                sumG += output.pixels(i - 1, j).g;
                sumB += output.pixels(i - 1, j).b;
                count++;
            }
            if (j > 0) {
                sumR += output.pixels(i, j - 1).r;
                sumG += output.pixels(i, j - 1).g;
                sumB += output.pixels(i, j - 1).b;
                count++;
            }
            if (i < input.height - 1) {
                sumR += temp.pixels(i + 1, j).r;
                sumG += temp.pixels(i + 1, j).g;
                sumB += temp.pixels(i + 1, j).b;
                count++;
            }
            if (j < input.width - 1) {
                sumR += temp.pixels(i, j + 1).r;
                sumG += temp.pixels(i, j + 1).g;
                sumB += temp.pixels(i, j + 1).b;
                count++;
            }

            sumR += temp.pixels(i, j).r;
            sumG += temp.pixels(i, j).g;
            sumB += temp.pixels(i, j).b;
            count++;

            output.pixels(i, j).r = static_cast<unsigned char>(sumR / 5);
            output.pixels(i, j).g = static_cast<unsigned char>(sumG / 5);
            output.pixels(i, j).b = static_cast<unsigned char>(sumB / 5);
        });

        Kokkos::deep_copy(temp.pixels, output.pixels);
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <Input_image>" << std::endl;
        return -1;
    }

    Kokkos::initialize(argc, argv);
    {
        Image input;
        try {
            input = readPPM(argv[1]);
        } catch (const std::exception &e) {
            std::cout << e.what() << std::endl;
            Kokkos::finalize();
            return -1;
        }

        int iterations = DENOISE_ITER;

        Image Jacobioutput;
        Jacobioutput.pixels = Kokkos::View<Pixel**>("Jacobioutput", input.height, input.width);
        Jacobioutput.width = input.width;
        Jacobioutput.height = input.height;

        Image GaussSeideloutput;
        GaussSeideloutput.pixels = Kokkos::View<Pixel**>("GaussSeideloutput", input.height, input.width);
        GaussSeideloutput.width = input.width;
        GaussSeideloutput.height = input.height;

        auto start = std::chrono::high_resolution_clock::now();
        jacobiDenoise(input, Jacobioutput, iterations);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "jacobiDenoise elapsed time: " << elapsed_seconds.count() << "s\n";

        writePPM("../res/DenoiseJacobi.ppm", Jacobioutput);

        start = std::chrono::high_resolution_clock::now();
        gaussSeidelDenoiseWavefront(input, GaussSeideloutput, iterations);
        end = std::chrono::high_resolution_clock::now();
        elapsed_seconds = end - start;
        std::cout << "gaussSeidelDenoiseWavefront elapsed time: " << elapsed_seconds.count() << "s\n";

        writePPM("../res/DenoiseGaussSeidel.ppm", GaussSeideloutput);
    }
    Kokkos::finalize();

    return 0;
}
