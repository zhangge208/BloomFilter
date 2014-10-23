all:strfind
strfind: main.o bloom.o hash.o
	cc -o strfind -Wall -pedantic hash.o bloom.o main.o
main.o:main.c 
	cc -o main.o -Wall -pedantic -ansi -c main.c
bloom.o:bloom.c bloom.h
	cc -o bloom.o -Wall -pedantic -ansi -c bloom.c
hash.o:hash.c hash.h
	cc -o hash.o -Wall -pedantic -ansi -c hash.c
clean:
	rm main.o bloom.o hash.o strfind
