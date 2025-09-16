CC = gcc
CFLAGS = -Wall -D_DEFAULT_SOURCE
LDFLAGS = -lGL -lGLU -lglut -lm
TARGET = casav2
SRC = casav2.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET)
