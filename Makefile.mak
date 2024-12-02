CC = gcc
CFLAGS = -Wall
TARGET = main
SRC = Curs.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)