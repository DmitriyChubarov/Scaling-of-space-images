CXX = clang++
CXXFLAGS = -std=c++17 -O2
SRC = $(wildcard *.cpp)
OUT = bin/scaling_img

all:
	mkdir -p bin
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)
