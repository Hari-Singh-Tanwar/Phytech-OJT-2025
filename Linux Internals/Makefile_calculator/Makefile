CC = gcc

TARGET = calculator

SOURCES = calculator.c


all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(SOURCES) -o $(TARGET)

run:
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
