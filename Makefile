CC = gcc
CFLAGS = -O0 -g -Wall -Wextra
TARGET = minierim

$(TARGET): minierim.c
	$(CC) $(CFLAGS) -o $(TARGET) minierim.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: run clean