CC=gcc
CFLAGS=-Wall -Wextra
TARGET=cmdcalc
OBJ = main.o calc.o decrypt.o

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)
main.o: main.c decrypt.h calc.h
	$(CC) $(CFLAGS) -c main.c
calc.o: calc.c calc.h
	$(CC) $(CFLAGs) -c calc.c
decrypt.o: decrypt.c decrypt.h
	$(CC) $(CFLAGS) -c decrypt.c

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET) 41 + 33 111 - 8 22 '*' 5 221 % 111 100 + 13 -k 2

.PHONY: clean run 
