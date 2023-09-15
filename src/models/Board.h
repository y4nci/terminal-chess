#ifndef BOARD_H
#define BOARD_H

#include "../constants.h"
#include "Piece.h"
#include "Point.h"
#include "../types.h"

#include <curses.h>
#include <vector>

class Board {
public:
    Board();
    Board(std::vector<Piece>& pieces);
    ~Board();

    std::vector<Piece>& getPieces();
    Point getCursor();

    void setPieces(std::vector<Piece>& pieces);
    void setCursor(Point cursor);

    Board operator=(Board& other);

    void selectPieceAtCursor(bool select);
    void moveSelectedToCursor();
    void display();
private:
    std::vector<Piece> pieces;
    Point cursor;
    int selectedIdx;
};

#endif
