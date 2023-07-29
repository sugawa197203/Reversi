SRC=$(wildcard src/*.c)
INCLUDE=include
TARGET=Reversi
LNCURSES=-lncurses

build: clean
	@mkdir build
	@echo Compile Stone...
	@$(CC) -c src/Stone.c -I $(INCLUDE) -o build/Stone.o
	@echo Compile Util...
	@$(CC) -c src/Util.c -I $(INCLUDE) -o build/Util.o
	@echo Compile Display...
	@$(CC) -c src/Display.c -I $(INCLUDE) $(LNCURSES) -o build/Display.o
	@echo Compile Reversi...
	@$(CC) src/Reversi.c build/Stone.o build/Util.o build/Display.o -o build/$(TARGET) -I $(INCLUDE) $(LNCURSES)

clean:
	@rm -r build

all:
	@rm -f ./Reversi
	@$(CC) $(SRC) -o Reversi -I $(INCLUDE) $(LNCURSES)
