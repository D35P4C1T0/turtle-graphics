# Makefile per compilare turtle.c

# Specifica il compilatore da utilizzare
CC = gcc

# Opzioni del compilatore
CFLAGS = -Wall -Wextra -std=c11

# Directory contenente i file sorgente
SRCDIR = src

# Directory in cui verranno messi i file oggetto
OBJDIR = obj

# Nome del file eseguibile
EXEC = turtle

# File sorgente
SRC = $(wildcard $(SRCDIR)/*.c)

# File oggetto generato
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Target predefinito
all: $(EXEC)

# Regola per creare l'eseguibile
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Regola per compilare i file oggetto
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Crea la directory per i file oggetto se non esiste
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Pulizia dei file intermedi e dell'eseguibile
clean:
	rm -rf $(OBJDIR) $(EXEC)

# Impedisci che 'clean' sia interpretato come un file
.PHONY: clean

