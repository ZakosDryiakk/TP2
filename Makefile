all: ExtQuickSort.o main.cpp
	g++ ExtQuickSort.o main.cpp -Wall -o Main

ExtQuickSort.o: ExtQuickSort.cpp
	g++ -c ExtQuickSort.cpp -Wall -o ExtQuickSort.o

clean:
	rm -f *.o Main

run:
	./Main