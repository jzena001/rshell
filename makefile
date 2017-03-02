CC=g++ 
CFLAGS=-Wall -Werror -ansi -pedantic
LDFLAGS=
SOURCES=main.cpp

all:makedir
	$(CC)$(CFLAGS) src/main.cpp -o bin/rshell
makedir:
	mkdir bin
