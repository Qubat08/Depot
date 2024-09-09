# Variables
CC=g++
CFLAGS=-Wall -O3 -fopenmp
LDFLAGS=
CFLAGS += $(shell pkg-config --cflags opencv4)
LDFLAGS += $(shell pkg-config --libs opencv4)

# Default target
all: directories opencv_test.pgr denoise.pgr

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
	rm -rf res
	rm -rf obj
