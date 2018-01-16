CC=clang
CFLAGS=-Wall -Wextra -Wpedantic

all: todo

todo: todo.c
	$(CC) $(CFLAGS) todo.c -o todo
