CC = g++
CFLAGS = -Wall -g -std=c++11 -I/opt/homebrew/opt/ncurses/include -D_XOPEN_SOURCE_EXTENDED
LDFLAGS = -lncursesw -L/opt/homebrew/opt/ncurses/lib
SRC_DIR = src

SOURCEFILES = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/models/*.cpp)
HEADERFILES = $(wildcard $(SRC_DIR)/*.h) $(wildcard $(SRC_DIR)/models/*.h)
MAIN = $(SRC_DIR)/main.cpp

terminal-chess: $(SOURCEFILES) $(HEADERFILES)
	$(CC)	$(CFLAGS)	-o	$@	$(SOURCEFILES)	$(LDFLAGS)

clean:
	rm -f terminal-chess
