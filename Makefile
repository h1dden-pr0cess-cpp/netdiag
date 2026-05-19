CC=gcc
CFLAGS=-Wall -Wextra -Iinclude

SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)

netdiag: $(OBJ)
	$(CC) $(OBJ) -o netdiag

clean:
	rm -f src/*.o netdiag
