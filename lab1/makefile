CC=clang
CFLAGS=-I.
DEPS = commands.h readtable.h

main: main.c commands.c
	$(CC) -o main main.c commands.c readtable.c $(CFLAGS)

clean:
	rm main output.txt
