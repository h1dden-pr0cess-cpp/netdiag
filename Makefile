CC=gcc

CFLAGS=-Wall -Wextra -Iinclude

SRC=$(wildcard src/*.c)

OBJ=$(patsubst src/%.c,build/%.o,$(SRC))

TARGET=netdiag


all: build $(TARGET)

build:
	mkdir -p build

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build $(TARGET)
