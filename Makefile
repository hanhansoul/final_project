all: main

main: main.o experiment_test.o data_input.o initialization.o node_function.o connection.o STRUCT.h NODE.h
	g++ -g main.o experiment_test.o data_input.o initialization.o node_function.o connection.o STRUCT.h NODE.h -o main

main.o: main.cpp 
	g++ -g -c main.cpp

experiment_test.o: experiment_test.cpp
	g++ -g -c experiment_test.cpp 

data_input.o: data_input.cpp 
	g++ -g -c data_input.cpp 

initialization.o: initialization.cpp 
	g++ -g -c initialization.cpp 

node_function.o: node_function.cpp 
	g++ -g -c node_function.cpp 

connection.o: connection.cpp NODE.h
	g++ -g -c connection.cpp 

clean:
	rm *o main
