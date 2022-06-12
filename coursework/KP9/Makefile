CC=gcc
LD=gcc

CCFLAGS=-Wall -pedantic -std=c99
LDFLAGS=-lquadmath

PROG=KP9
OBJ=main.o item.o sort_hoar.o user_interface.o vitem.o

build: $(PROG)

$(PROG): $(OBJ)
	$(LD) $(OBJ) -o $(PROG) $(LDFLAGS)

.c.o:
	$(CC) $(CCFLAGS) -c $< -o $@

main.o: user_interface.h vitem.h sort_hoar.h item.h

user_interface.o: user_interface.h vitem.h item.h

item.o: item.h

sort_hoar.o: sort_hoar.h vitem.h item.h

vitem.o: vitem.h item.h

clean:
	rm $(PROG) $(OBJ)
