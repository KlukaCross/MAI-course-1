CC=gcc
LD=gcc

CCFLAGS=-Wall -pedantic -std=c99
LDFLAGS=

PROG=KP8
OBJ=main.o list.o svint.o user_interface.o

build: $(PROG)

$(PROG): $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o $(PROG)

.c.o:
	$(CC) $(CCFLAGS) -c $< -o $@

main.o: user_interface.h list.h

list.o: list.h

user_interface.o: user_interface.h list.h svint.h

clean:
	rm $(PROG) $(OBJ)

