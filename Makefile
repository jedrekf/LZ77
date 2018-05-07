CXX = g++
CXXFLAGS = -std=c++11 -Wall

OBJECTS = main.o file_loader.o

main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm *.o main

$(OBJECTS): functions.h
