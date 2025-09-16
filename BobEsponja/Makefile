# Makefile para o projeto Bob Esponja em OpenGL

# --- Variáveis ---

# O compilador que será usado (geralmente gcc em sistemas Linux)
CC = gcc

# O nome do arquivo executável que será gerado
EXEC = bob_esponja

# O nome do arquivo fonte .c
SRCS = bob_esponja.c

# Flags de compilação. -Wall ativa todos os avisos (boa prática)
CFLAGS = -Wall

# Bibliotecas (libs) que precisam ser linkadas. 
# A ordem pode ser importante: -lGLU e -lglut dependem de -lGL.
LIBS = -lglut -lGLU -lGL -lm

# --- Regras ---

# A regra padrão, que será executada quando você digitar "make"
# Ela depende do executável. Se o executável não existir ou estiver
# desatualizado, a regra para criá-lo será chamada.
all: $(EXEC)

# Regra para criar o arquivo executável.
# Depende do arquivo fonte. Se o .c for modificado,
# esta regra será executada novamente na próxima vez que "make" for chamado.
$(EXEC): $(SRCS)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRCS) $(LIBS)

# Regra para limpar os arquivos gerados pela compilação.
# Muito útil para começar uma compilação "limpa".
clean:
	rm -f $(EXEC)

# Declara que 'all' e 'clean' não são nomes de arquivos.
# É uma boa prática para evitar conflitos.
.PHONY: all clean