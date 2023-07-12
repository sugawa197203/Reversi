Compiler=gcc

SRC=src/Reversi.c
INCLUDE=include
TARGET=Reversi
LDFLAGS=-lncurses

all: cboard

cboard: clean
	$(Compiler) -o $(TARGET) $(SRC) -I $(INCLUDE) $(LDFLAGS)

clean:
	rm -f $(TARGET)
