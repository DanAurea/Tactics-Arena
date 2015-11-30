CC=gcc
CFLAGS=-g -Wall -std=c99
LDFLAGS=-lm
EXEC=bin/tacticsArena
SRC= $(wildcard src/*.c)
OBJ= $(SRC:.c=.o)
INC= include/

$(EXEC): $(OBJ)
	$(CC) -o $@ $^
	@echo "\nOn reconstruit $@ a cause de $?"

src/%.o: %.c 
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

clean:
	@rm -rf ./$(OBJ)

mrproper: clean
	@rm -rf $(EXEC)