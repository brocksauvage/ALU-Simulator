CC=gcc

CFLAGS = -ansi -std=c99 -pedantic -Wall -m32

ALU: ALUSimulator_Main.c RegisterFile_01.c ALUSimulator.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm ALU