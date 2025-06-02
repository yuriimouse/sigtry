# Makefile
CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET ?= test_sigtry
SRC = main.c
HDR = sigtry.h

.PHONY: all clean run

all: clean $(TARGET)

$(TARGET): $(SRC) $(HDR)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
