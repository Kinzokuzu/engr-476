CC=gcc
CFLAGS=-I.
DEPS = ticTacToe.h

main: main.c ticTacToe.c
	$(CC) -o main main.c ticTacToe.c

test: unitTests.c ticTacToe.c
	$(CC) -o test unitTests.c ticTacToe.c

clean:
	rm main test
