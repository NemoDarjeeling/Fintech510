CCFLAGS=--std=C++11 -pedantic -Wall -Werror -ggdb3

correl_matrix: main.o asset.o
	g++ $(CFLAGS) -o correl_matrix main.o asset.o

main.o: main.cpp asset.hpp
	g++ -c $(CFLAGS) main.cpp

asset.o: asset.cpp asset.hpp
	g++ -c $(CFLAGS) asset.cpp

