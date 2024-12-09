CC = gcc
CFLAGS = -Wall -std=c99 -O2
OBJ = main.o simulation.o search.o
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	@echo "Linking object files to create $(TARGET)..."
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.c simulation.h
	@echo "Compiling main.c..."
	$(CC) $(CFLAGS) -c main.c

simulation.o: simulation.c simulation.h search.h
	@echo "Compiling simulation.c..."
	$(CC) $(CFLAGS) -c simulation.c

search.o: search.c search.h
	@echo "Compiling search.c..."
	$(CC) $(CFLAGS) -c search.c

clean:
	@echo "Cleaning up..."
	rm -f $(OBJ) $(TARGET)
