all: scanner.o

scanner.o: scanner.cpp
	g++ -c scanner.cpp

test: scanner.o
	g++ -o scanner_test scanner.o scanner_test.cpp -lgtest -lpthread
	./scanner_test

clean:
	rm -f *.o scanner_test
