CC=gcc

CFLAGS = -ansi -std=c99 -pedantic -Wall -m32

ALU: RegisterFile_01.c main.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm ALU