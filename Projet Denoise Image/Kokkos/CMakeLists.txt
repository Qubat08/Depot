cmake_minimum_required(VERSION 3.10)
project(MonProjet)

set(CMAKE_CXX_STANDARD 14)

# Ajouter le chemin d'installation de Kokkos
set(Kokkos_DIR "/home/qbatiste/CHPS0801/kokkos/build/lib64/cmake/Kokkos")

find_package(Kokkos REQUIRED)

add_executable(denoise denoise.cpp)

target_link_libraries(denoise Kokkos::kokkos)