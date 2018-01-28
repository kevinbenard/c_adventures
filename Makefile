CC=clang
CFLAGS=-Wall -Wextra -Wpedantic -g
INCLUDES=.

all: todo

todo: todo.h todo.c main.c
	$(CC) $(CFLAGS) -I$(INCLUDES) todo.c main.c -o todo

test: todo
	rm ./data.db
	./todo one two three
	./todo 4 five six seven
	./todo -l

clean:
	rm -rf ./todo ./todo.dSYM/
