CC=gcc
LD=gcc

CCFLAGS=-Wall -pedantic -std=c99
LDFLAGS=

PROG=lab24
OBJ=main.o sorting_station.o building.o user_interface.o token_struct.o token_queue.o token_stack.o token_tree.o token_vector.o token_tree_stack.o

build: $(PROG)

$(PROG): $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o $(PROG) -lm

.c.o:
	$(CC) $(CCFLAGS) -c $< -o $@

main.o: token_tree.h token_queue.h user_interface.h sorting_station.h error_struct.h building.h token_struct.h
sorting_station.o: sorting_station.h token_stack.h token_queue.h error_struct.h token_struct.h
building.o: building.h token_queue.h error_struct.h token_tree_stack.h token_tree.h token_struct.h
user_interface.o: user_interface.h token_queue.o token_tree.h token_vector.h error_struct.h token_struct.h
token_queue.o: token_queue.h token_struct.h
token_stack.o: token_stack.h token_struct.h
token_tree.o: token_tree.h token_struct.h
token_vector.o: token_vector.h token_struct.h
token_tree_stack.o: token_tree_stack.h token_tree.h token_struct.h

clean:
	rm $(PROG) $(OBJ)

