CC=g++-9 -O3 -std=c++17
CFLAGS=-I./include
LIBS=-ltbb

.PHONY: build clean

build: clean
	mkdir build && $(CC) -o build/short src/short.cpp $(CFLAGS) $(LIBS)

clean:
	rm -rf build
