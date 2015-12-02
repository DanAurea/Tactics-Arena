CC=gcc
CFLAGS=-g -Wall -std=c99
LDFLAGS=-lm
EXEC=bin/tacticsArena
SRC= $(wildcard src/*.c)
UNITS= $(wildcard src/units/*.c)
OBJUNITS= $(UNITS:.c=.o)
OBJ= $(SRC:.c=.o)
INC= include/

$(EXEC): $(OBJ) $(OBJUNITS)
	$(CC) -o $@ $^
	@echo "\nOn reconstruit $@ a cause de $?"

src/gameEngine.o: $(INC)gameEngine.h

src/unit.o: $(INC)unit.h

src/grid.o: $(INC)gameEngine.h $(INC)menu.h

src/menu.o: $(INC)gameEngine.h $(INC)menu.h

src/%.o: %.c $(INC)gameEngine.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

src/units/%.o: %.c $(INC)gameEngine.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)


clean:
	@rm -rf ./$(OBJ)

mrproper: clean
	@rm -rf $(EXEC)
