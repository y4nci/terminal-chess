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
    if (cursor.x > 7 || cursor.x < 0 || cursor.y > 7 || cursor.y < 0) return;

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
            if (piece.getIsDead()) continue;
            if (!select && i != this->selectedIdx) continue;
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
    bool moveSuccessful = true;
    
    if (selectedIdx == -1) return;

    selected = this->pieces.at(selectedIdx);

    for (int i = 0; i < this->pieces.size(); i++) {
        Piece piece = this->pieces.at(i);

        if (piece.getCoordinates() == target) {
            if (piece.getIsDead()) {
                moveSuccessful = false;
                continue;
            }
            if (i == this->selectedIdx) return;
            if (piece.getPlayer() == selected.getPlayer()) return;

            this->pieces.at(i).setIsDead(true);

            moveSuccessful = true;

            break;
        }
    }

    if (!moveSuccessful) return;

    this->pieces.at(selectedIdx).setCoordinates(target);
    this->pieces.at(selectedIdx).setIsSelected(false);
}

void Board::display() {
    std::vector<std::wstring> displayedBoard (CHESS_BOARD);
    std::vector<Point> possibleMoves;
    Piece selected;
    Point coordinates;

    clear();

    for (Piece piece : this->pieces) {
        Point coordinates = piece.getCoordinates();
        Point displayedCoordinates = Point ((coordinates.x + 1) * 2, (coordinates.y * 4) + 3);

        if (piece.getIsDead()) continue;
        
        displayedBoard[displayedCoordinates.x][displayedCoordinates.y] = piece.getUnicode()[0];
    }

    for (int i = 0; i < displayedBoard.size(); i++) {
        mvaddwstr(i, 0, displayedBoard.at(i).c_str());
    }

    if (this->selectedIdx != -1) {
        selected = this->pieces.at(this->selectedIdx);

        coordinates = selected.getCoordinates();
        Point displayedCoordinates = Point ((coordinates.x + 1) * 2, (coordinates.y * 4) + 3);

        attron(COLOR_PAIR(Colouring::SELECTED)); // Use color pair 1 (yellow text on black background) for highlighting
        mvaddwstr(displayedCoordinates.x, displayedCoordinates.y - 1, L">");
        mvaddwstr(displayedCoordinates.x, displayedCoordinates.y, selected.getUnicode().c_str());
        mvaddwstr(displayedCoordinates.x, displayedCoordinates.y + 1, L"<");
        attroff(COLOR_PAIR(Colouring::SELECTED)); // Turn off the color pair
    
        possibleMoves = selected.getPossibleMoves(this->pieces);

        attron(COLOR_PAIR(Colouring::POSSIBLE_MOVE));
        
        for (Point possibleMove : possibleMoves) {
            Point displayedMove = Point ((possibleMove.x + 1) * 2, (possibleMove.y * 4) + 3);

            mvaddwstr(displayedMove.x, displayedMove.y - 2, L"║");
            mvaddwstr(displayedMove.x, displayedMove.y + 2, L"║");

            mvaddwstr(displayedMove.x - 1, displayedMove.y - 1, L"═══");
            mvaddwstr(displayedMove.x + 1, displayedMove.y - 1, L"═══");
        }

        attroff(COLOR_PAIR(Colouring::POSSIBLE_MOVE));
    }

    attron(COLOR_PAIR(Colouring::CURSOR));

    mvaddwstr((this->cursor.x + 1) * 2, (this->cursor.y * 4) + 2, L"-");
    mvaddwstr((this->cursor.x + 1) * 2, (this->cursor.y * 4) + 4, L"-");
    
    attroff(COLOR_PAIR(Colouring::CURSOR));
}
