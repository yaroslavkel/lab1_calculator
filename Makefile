CC=gcc
CFLAGS=-Wall -Wextra
TARGET=cmdcalc
SOURCES=main.c calc.c decrypt.c

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET) 41 + 33 111 - 8 22 '*' 5 221 % 111 100 + 13 -k 2

.PHONY: clean run 
