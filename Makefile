all: superstring2

superstring2: Source.o Superstring.o SumGraph.o FindPath.o FuncSumgraph.o FSM.o
        g++ Source.o Superstring.o SumGraph.o FindPath.o FSM.o -o superstring2

Source.o: Source.cpp Superstring.o
        g++ -c Source.cpp

SumGraph.o: SumGraph.cpp FSM.o
        g++ -c SumGraph.cpp

FSM.o: FSM.cpp FSM.h
        g++ -c FSM.cpp

FuncSumgraph.o: FuncSumgraph.cpp
        g++ -c FuncSumgraph.cpp

Superstring.o: Superstring.cpp FindPath.o
        g++ -c Superstring.cpp

FindPath.o: FindPath.cpp
        g++ -c FindPath.cpp

clean:
        rm -rf *.o superstring2                          
