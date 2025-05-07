# Nom de l'exécutable final
TARGET = main

# Compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -g

# Dossier contenant les fichiers source
SRC_DIR = sources

# Dossier contenant les fichiers d'en-tête
INC_DIR = includes

# Fichier source principal (main.c)
MAIN_SRC = $(SRC_DIR)/main.c

# Tous les fichiers source (sauf main.c)
SRCS = $(filter-out $(MAIN_SRC), $(wildcard $(SRC_DIR)/*.c))

# Fichiers objets générés à partir des sources
OBJS = $(SRCS:.c=.o)

# Règle par défaut : compilation de l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -I$(INC_DIR) -o $(TARGET) $(MAIN_SRC) $(OBJS)

# Compilation des fichiers objets
%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Nettoyage des fichiers générés
clean:
	rm -f $(OBJS) $(TARGET)

# Règle pour exécuter le programme
run: $(TARGET)
	./$(TARGET)
