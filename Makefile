.PHONY: build clean
cc = g++

build: main

main: main.o lib_symbol.o
	$(cc) -Wall -Wextra -Werror -o main main.o lib_symbol.o

lib_symbol.o: lib_symbol.cpp lib_symbol.hpp
	$(cc) -Wall -Wextra -Werror -c lib_symbol.cpp

main.o: main.cpp lib_symbol_strings.hpp
	$(cc) -Wall -Wextra -Werror -c main.cpp

clean:
	del *.o main.exe