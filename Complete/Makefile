Compiler=gcc

SRC=src/Reversi.c
INCLUDE=include
TARGET=Reversi
LDFLAGS=-lncurses

reversi: clean
	$(Compiler) -o $(TARGET) $(SRC) -I $(INCLUDE) $(LDFLAGS) -O3

clean:
	rm -f $(TARGET)
