CC = gcc
EXEC = recorte
SRC = recorte.c
CFLAGS = -Wall -g
LIBS = -lglut -lGLU -lGL -lm

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

run: all
	./$(EXEC)

clean:
	rm -f $(EXEC)