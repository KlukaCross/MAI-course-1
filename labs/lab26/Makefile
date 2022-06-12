CC=gcc
LD=gcc

CCFLAGS=-Wall -pedantic -std=c99
LDFLAGS=

PROG=lab26
OBJ=main.o list.o

build: $(PROG)

$(PROG): $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o $(PROG)

.c.o:
	$(CC) $(CCFLAGS) -c $< -o $@

main.o: list.h

list.o: list.h

clean:
	rm $(PROG) $(OBJ)