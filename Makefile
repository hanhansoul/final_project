all: main

main: main.o experiment_test.o data_input.o STRUCT.h
	g++ -g -o main main.o experiment_test.o data_input.o STRUCT.h

main.o: main.cpp
	g++ -g -c main.cpp

experiment_test.o: experiment_test.cpp STRUCT.h
	g++ -g -c experiment_test.cpp STRUCT.h

data_input.o: data_input.cpp STRUCT.h
	g++ -g -c data_input.cpp STRUCT.h

clean:
	rm *o *gch main
