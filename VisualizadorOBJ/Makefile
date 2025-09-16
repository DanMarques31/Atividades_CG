CC = gcc
CFLAGS = -Wall -g

# Bibliotecas necessárias para OpenGL, GLU e GLUT
LIBS = -lglut -lGLU -lGL -lm

SRC = visualizador.c
TARGET = visualizador

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)
	@echo "Compilação concluída! Execute com: ./$(TARGET) <OBJfiles/arquivo.obj>"

clean:
	rm -f $(TARGET)
	@echo "Arquivos compilados removidos."