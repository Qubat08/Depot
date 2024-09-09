ifeq ($(arg1), 0)
# Variables
CC=g++
CFLAGS=-Wall -O3
LDFLAGS=
CFLAGS += $(shell pkg-config --cflags opencv4)
LDFLAGS += $(shell pkg-config --libs opencv4)

# Default target
all: directories opencv_test.pgr 

directories: 
	mkdir -p obj
	mkdir -p res

# Target for opencv_test.pgr
opencv_test.pgr: obj/opencv_simple.o obj/gaussianNoise.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Target for jacobiDenoise.pgr
denoise.pgr: obj/denoise.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Rule to compile source files to object files
obj/%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Cleaning rules
proper:
	rm -f obj/*.o
	rm -rf res

clean:
	rm -rf obj/*.o *.pgr
	rm -rf res obj build

else

CC=clang -fopenmp -fopenmp-targets=nvptx64-nvidia-cuda
CFLAGS=-O3 -Wall
LDFLAGS=-lm -L/apps/2021/gcc/10.2/lib64/ -lstdc++

EXEC=denoise.pgr

all : directories denoise.pgr

directories: 
	mkdir -p obj
	mkdir -p res

denoise.pgr: obj/denoise.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)


obj/%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@


proper:
	rm -f obj/*.o
	rm -rf res

clean:
	rm -rf obj/*.o *.pgr
	rm -rf res
	rm -rf obj

endif
