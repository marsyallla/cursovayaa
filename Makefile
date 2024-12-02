CC = gcc
CFLAGS = -Wall
TARGET = main
SRC = Curs.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)