.PHONY: all clean

BIN = main

CPP = taller.cpp main.cpp
OBJ = $(CPP:.cpp=.o)
SRC = $(CPP)

all: main

clean:
	rm -f $(BIN) $(OBJ)

main: main.o taller.o
	g++ -o $@ $^

%.o: %.cpp
	g++ -c -std=c++17 -o $@ $<
