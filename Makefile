CC=gcc
CFLAGS=-pedantic -Wall -O2
SOURCES=main.o bignum.o
EXECUTABLE=tp3

all: $(EXECUTABLE)

tp3: main.o bignum.o
	$(CC) $(SOURCES) -o $(EXECUTABLE)

main.o: main.c bignum.h
	$(CC) $(CFLAGS) -lm -c main.c

bignum.o: bignum.c bignum.h
	$(CC) $(CFLAGS) -lm -c bignum.c

clean:
	rm *.o tp3