all: main

main: main.o experiment_test.o data_input.o initialization.o node_function.o connection.o STRUCT.h NODE.h
	g++ -g main.o experiment_test.o data_input.o initialization.o node_function.o connection.o STRUCT.h NODE.h -o main

main.o: main.cpp NODE.h STRUCT.h
	g++ -g -c main.cpp

experiment_test.o: experiment_test.cpp STRUCT.h
	g++ -g -c experiment_test.cpp 

data_input.o: data_input.cpp NODE.h STRUCT.h
	g++ -g -c data_input.cpp 

initialization.o: initialization.cpp 
	g++ -g -c initialization.cpp 

node_function.o: node_function.cpp NODE.h STRUCT.h
	g++ -g -c node_function.cpp 

connection.o: connection.cpp NODE.h STRUCT.h
	g++ -g -c connection.cpp 

NODE.h: STRUCT.h

clean:
	rm *o main
