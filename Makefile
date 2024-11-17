# Compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -I./include

# Sources
SRCS = src/main.c src/flags.c src/file_ops.c src/display.c

# Objets
OBJS = $(SRCS:.c=.o)

# Nom de l'exécutable
TARGET = ls

# Règle par défaut
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)
	rm -f $(OBJS)

# Nettoyage des fichiers générés
clean:
	rm -f $(OBJS) $(TARGET)
