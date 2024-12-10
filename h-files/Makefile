CC = gcc
CFLAGS = -Wall -std=c99 -O2
OBJ = inverse_function.o simulation.o search.o
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	@echo "Linking object files to create $(TARGET)..."
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

inverse_function.o: inverse_function.c simulation.h
	@echo "Compiling inverse_function.c..."
	$(CC) $(CFLAGS) -c inverse_function.c

simulation.o: simulation.c simulation.h search.h
	@echo "Compiling simulation.c..."
	$(CC) $(CFLAGS) -c simulation.c

search.o: search.c search.h
	@echo "Compiling search.c..."
	$(CC) $(CFLAGS) -c search.c

clean:
	@echo "Cleaning up..."
	rm -f $(OBJ) $(TARGET)