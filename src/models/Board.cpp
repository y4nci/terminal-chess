#include "Board.h"

Board::Board() {
    this->pieces = { Piece () };
    this->cursor.x = 0, this->cursor.y = 0;
    this->selectedIdx = -1;
}

Board::Board(std::vector<Piece>& pieces) {
    this->pieces = pieces;
    this->cursor.x = 0, this->cursor.y = 0;
    this->selectedIdx = -1;
}

Board::~Board() { }

std::vector<Piece>& Board::getPieces() {
    return this->pieces;
}

Point Board::getCursor() {
    return this->cursor;
}

void Board::setPieces(std::vector<Piece>& pieces) {
    this->pieces = pieces;
}

void Board::setCursor(Point cursor) {
    this->cursor = cursor;
}

Board Board::operator=(Board& other) {
    this->cursor = other.cursor;
    this->pieces = other.pieces;
    this->selectedIdx = other.selectedIdx;

    return *this;
}

void Board::selectPieceAtCursor(bool select) {
    for (int i = 0; i < this->pieces.size(); i++) {
        Piece piece = this->pieces.at(i);
        Point coordinates = piece.getCoordinates();
        
        if (coordinates == this->cursor) {
            if (this->selectedIdx != -1 && select) {
                this->pieces.at(this->selectedIdx).setIsSelected(false);
            }

            piece.setIsSelected(select);

            if (select) {
                this->selectedIdx = i;
            } else {
                this->selectedIdx = -1;
            }
            break;
        }
    }
}

void Board::moveSelectedToCursor() {
    Point target = this->cursor;
    Piece selected;
    
    if (selectedIdx == -1) return;

    selected = this->pieces.at(selectedIdx);

    for (int i = 0; i < this->pieces.size(); i++) {
        Piece piece = this->pieces.at(i);

        if (i == this->selectedIdx) return;

        if (piece.getCoordinates() == target) {
            if (piece.getIsDead()) return;
            if (piece.getType() == selected.getType()) return;

            this->pieces.at(i).setIsDead(true);

            break;
        }
    }

    this->pieces.at(selectedIdx).setCoordinates(target);
    this->pieces.at(selectedIdx).setIsSelected(false);
}

void Board::display() {
    std::vector<std::wstring> displayedBoard (CHESS_BOARD);
    Piece selected;

    for (Piece piece : this->pieces) {
        Point coordinates = piece.getCoordinates();
        Point displayedCoordinates = Point ((coordinates.x + 1) * 2, (coordinates.y * 4) - 1);

        if (piece.getIsDead()) continue;
        
        displayedBoard[displayedCoordinates.x][displayedCoordinates.y] = piece.getUnicode();
    }

    for (int i = 0; i < 8; i++) {
        mvprintw(i, 0, (char*) displayedBoard[i].c_str());  // TODO: the type casting might be a problem
    }

    if (this->selectedIdx != -1) {
        selected = this->pieces.at(this->selectedIdx);
    } else {
        return;
    }

    Point coordinates = selected.getCoordinates();
    Point displayedCoordinates = Point ((coordinates.x + 1) * 2, (coordinates.y * 4) - 1);
    std::vector<Point> possibleMoves;

    attron(COLOR_PAIR(Colouring::SELECTED)); // Use color pair 1 (yellow text on black background) for highlighting
    mvprintw(displayedCoordinates.x, displayedCoordinates.y - 1, ">");
    mvprintw(displayedCoordinates.x, displayedCoordinates.y, "%c", selected.getUnicode());
    mvprintw(displayedCoordinates.x, displayedCoordinates.y + 1, "<");
    attroff(COLOR_PAIR(Colouring::SELECTED)); // Turn off the color pair

    possibleMoves = selected.getPossibleMoves(this->pieces);

    attron(COLOR_PAIR(Colouring::POSSIBLE_MOVE));
    
    for (Point possibleMove : possibleMoves) {
        Point displayedMove = Point ((coordinates.x + 1) * 2, (coordinates.y * 4) - 1);

        mvprintw(displayedMove.x, displayedMove.y - 2, "║");
        mvprintw(displayedMove.x, displayedMove.y + 2, "║");

        mvprintw(displayedMove.x - 1, displayedMove.y - 1, "═══");
        mvprintw(displayedMove.x + 1, displayedMove.y - 1, "═══");
    }

    attroff(COLOR_PAIR(Colouring::POSSIBLE_MOVE));
}
