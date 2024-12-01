CC = gcc
CFLAGS = -Wall
TARGET = curs
SRC = main.c

all: $(TARGET)

$(TARGET): main.c
    $(CC) $(CFLAGS) -o $(TARGET) main.c

clean:
    rm -f $(TARGET)