
# This is a make file

CC = gcc #compilier
CFLAGS = -g 

all:
	$(CC) main.c list.c files.c -o all_test

main: main.c list.o files.o
	$(CC) -o main main.c

list: list.c
	$(CC) -c list.c -o list.o

files: files.c
	$(CC) -c files.c -o files.o
clean:
	rm main.o list.o files.o
