CC=gcc
CFLAGS=-g -Wall -std=c99
EXEC=bin/tacticsArena
SRC= $(wildcard src/*.c)
OBJ= $(SRC:.c=.o)
INC= include/

$(EXEC): $(OBJ)
	$(CC) -o $@ $^
	@echo "\nOn reconstruit $@ a cause de $?"

%.o: %.c 
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@rm -rf ./$(OBJ)

mrproper: clean
	@rm -rf $(EXEC)