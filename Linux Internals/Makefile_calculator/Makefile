CC = gcc

TARGET = calculator

SOURCES = calculator.c

CFLAGS = -g -Wall -O0

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

run:
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
