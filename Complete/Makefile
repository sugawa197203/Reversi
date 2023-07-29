SRC=$(wildcard src/*.c)
INCLUDE=include
TARGET=Reversi
LDFLAGS=-lncurses

reversi: clean
	$(CC) $(SRC) -o $(TARGET) -I $(INCLUDE) $(LDFLAGS) -O3

clean:
	rm -f $(TARGET)
