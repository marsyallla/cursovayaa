CC = gcc
CFLAGS = -Wall
TARGET = main
SRC = Zheng.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)