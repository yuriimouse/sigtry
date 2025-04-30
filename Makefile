CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = test_sigtry
SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)
