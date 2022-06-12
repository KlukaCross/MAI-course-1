CC=gcc
LD=gcc

CCFLAGS=-Wall -pedantic -std=c99
LDFLAGS=

PROG=lab23
OBJ=main.o tenum.o villages.o

build: $(PROG)

$(PROG): $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o $(PROG)

.c.o:
	$(CC) $(CCFLAGS) -c $< -o $@

main.o: tenum.h

tenum.o: tenum.h

villages.o: villages.h

clean:
	rm $(PROG) $(OBJ)
