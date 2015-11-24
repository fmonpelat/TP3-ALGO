CC=gcc
CFLAGS=-pedantic -Wall -g
SOURCES=main.o bignum.o simplecalc.o
EXECUTABLE=tp3

all: $(EXECUTABLE)

tp3: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -lm -o $(EXECUTABLE)

main.o: main.c bignum.h
	$(CC) $(CFLAGS) -c main.c

bignum.o: bignum.h bignum.c
	$(CC) $(CFLAGS) -c bignum.c

simplecalc.o: simplecalc.h simplecalc.c
	$(CC) $(CFLAGS) -c simplecalc.c
clean:
	rm *.o tp3
