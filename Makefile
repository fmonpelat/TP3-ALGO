CC=gcc
CFLAGS=-pedantic -Wall -O2
SOURCES=main.o bignum.o
EXECUTABLE=tp3

all: $(EXECUTABLE)

tp3: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -lm -o $(EXECUTABLE)

main.o: main.c bignum.h
	$(CC) $(CFLAGS) -c main.c

bignum.o: bignum.h bignum.c
	$(CC) $(CFLAGS) -c bignum.c

clean:
	rm *.o tp3
