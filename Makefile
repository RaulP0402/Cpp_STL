CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic -g

TARGET = test
SRC = main.cpp
HDR = vector.h
OBJ = main.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o : %.cpp $(HDR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)