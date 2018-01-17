CC=clang
CFLAGS=-Wall -Wextra -Wpedantic -g

all: todo

todo: todo.c
	$(CC) $(CFLAGS) todo.c -o todo

run: todo
	rm ./data.db
	./todo one two three
	./todo 4 five six seven
	./todo -l

clean:
	rm -rf ./todo ./todo.dSYM/
