CC = gcc
CFLAGS = -Wall
TARGET = Curs
SRC = main.c

all: $(TARGET)

$(TARGET): main.c
    $(CC) $(CFLAGS) -o $(TARGET) main.c

clean:
    rm -f $(TARGET)
