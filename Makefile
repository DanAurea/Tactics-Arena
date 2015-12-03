CC=gcc
CFLAGS=-g -Wall -std=c99
LDFLAGS=-lm
EXEC=bin/tacticsArena
SRC= $(wildcard src/*.c) $(wildcard src/units/*.c)
OBJ= $(SRC:.c=.o)
INC= include/

$(EXEC): $(OBJ)
	@$(CC) -o $@ $^

src/gameEngine.o: $(INC)gameEngine.h $(INC)listes.h $(INC)grid.h $(INC)menu.h $(INC)terminal.h $(INC)manageString.h $(INC)unit.h

src/manageString.o: $(INC)gameEngine.h

src/unit.o: $(INC)gameEngine.h $(INC)unit.h $(INC)unitType.h

src/grid.o: $(INC)gameEngine.h $(INC)gameEngine.h

src/menu.o: $(INC)gameEngine.h $(INC)menu.h $(INC)terminal.h $(INC)manageString.h

src/listes.o: $(INC)gameEngine.h $(INC)menu.h

src/terminal.o: $(INC)terminal.h

src/%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

src/units/%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

clean:
	@rm -rf ./$(OBJ)

mrproper: clean
	@rm -rf $(EXEC)
