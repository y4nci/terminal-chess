CC = g++
CFLAGS = -Wall -g -std=c++20 -I/opt/homebrew/opt/ncurses/include
LDFLAGS= -lncursesw -L/opt/homebrew/opt/ncurses/lib 
SRC_DIR = src

SOURCEFILES = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/models/*.cpp)
HEADERFILES = $(wildcard $(SRC_DIR)/*.h) $(wildcard $(SRC_DIR)/models/*.h)
MAIN = $(SRC_DIR)/main.cpp

all: $(SOURCEFILES) $(HEADERFILES)
	$(CC) $(CFLAGS) $(LDFLAGS) -o terminal-chess $(SOURCEFILES)

clean:
	rm -f terminal-chess
