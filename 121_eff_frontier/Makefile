CCFLAGS=--std=C++11 -pedantic -Wall -Werror -ggdb3

efficient_frontier: main.o portfolio.o
	g++ $(CFLAGS) -o efficient_frontier main.o portfolio.o

main.o: main.cpp portfolio.hpp
	g++ -c $(CFLAGS) main.cpp

portfolio.o: portfolio.cpp portfolio.hpp
	g++ -c $(CFLAGS) portfolio.cpp