CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

OBJECTS = main.o file_loader.o decompress.o

main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm *.o main

$(OBJECTS): functions.h structs.h
