CC=gcc
CFLAGS=-g -Wall -std=c99
LDFLAGS= -lSDL_image `sdl-config --libs --cflags` -lESDL -lm
EXEC=bin/tacticsArena

SRC= $(wildcard src/*/*.c && src/*.c)
OBJ= $(SRC:.c=.o)

INC= include/
engine   = $(INC)game/engine.h
pawns    = $(INC)game/pawns.h
listes   = $(INC)game/listes.h
pathList = $(INC)game/pathList.h
turn     = $(INC)game/turn.h
string   = $(INC)controller/manageString.h
signal   = $(INC)controller/manageSignal.h
terminal = $(INC)controller/terminal.h
grid     = $(INC)display/grid.h
menu     = $(INC)display/menu.h
units    = $(INC)units/unit.h


$(EXEC): $(OBJ)
	@$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

src/game/main.o: $(engine) $(pawns) $(listes) $(grid) $(menu) $(terminal) $(string) $(signal) $(units)

src/game/engine.o: $(engine) $(pawns) $(listes) $(grid) $(menu) $(terminal) $(string) $(signal) $(units) $(pathList) $(turn)

src/game/turn.o: $(engine) $(pawns) $(listes) $(grid) $(menu) $(terminal) $(string) $(signal) $(units) $(turn)

src/game/listes.o: $(engine) $(pawns) $(listes) $(string)

src/game/pathList.o: $(engine)

src/controller/manageString.o: $(engine)

src/controller/manageSignal.o: $(engine) $(pawns) $(listes) $(terminal) $(units) $(pathList)

src/units/unit.o: $(engine) $(pawns) $(listes) $(units)

src/display/grid.o: $(engine) $(grid) $(terminal) $(string)

src/display/menu.o: $(engine) $(pawns) $(menu) $(grid) $(terminal) $(string)

src/controller/terminal.o: $(terminal)

src/%.o: src/%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

.PHONY: doc

doc: 
	@doxygen configDoc && cd doc/latex && make && mv refman.pdf ../man.pdf


clean:
	@rm -rf ./$(OBJ)

mrproper: clean
	@rm -rf $(EXEC)