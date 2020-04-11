all: superstring2

superstring2: Source.o Superstring.o SumGraph.o FindPath.o
    g++ Source.o Superstring.o SumGraph.o FindPath.o -o superstring2

Source.o: Source.cpp Superstring.o
    g++ -c Source.cpp

SumGraph.o: SumGraph.cpp SumGraph.hpp
    g++ -c SumGraph.cpp

Superstring.o: Superstring.cpp FindPath.o
    g++ -c Superstring.cpp

FindPath.o: FindPath.cpp
    g++ -c FindPath.cpp

clean:
  rm -rf *.o superstring2
