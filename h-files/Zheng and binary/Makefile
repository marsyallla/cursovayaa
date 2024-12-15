CC = gcc
CFLAGS = -Wall -std=c99 -O2
OBJ = main.o simulation.o 
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	@echo "Linking object files to create $(TARGET)..."
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

inverse_function.o: main.c simulation.h
	@echo "Compiling main.c..."
	$(CC) $(CFLAGS) -c mainc

simulation.o: simulation.c simulation.h 
	@echo "Compiling simulation.c..."
	$(CC) $(CFLAGS) -c simulation.c

clean:
	@echo "Cleaning up..."
	rm -f $(OBJ) $(TARGET)