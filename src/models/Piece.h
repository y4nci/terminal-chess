#ifndef PIECE_H
#define PIECE_H

#include "../constants.h"
#include "Point.h"
#include "../types.h"

#include <vector>

class Piece {
public:
    Piece();
    Piece(PieceType piece, Point coordinates, PlayerType player);
    ~Piece();
    
    PieceType getType();
    Point getCoordinates();
    PlayerType getPlayer();
    bool getIsDead();
    std::wstring getUnicode();

    void setType(PieceType piece);
    void setCoordinates(Point coordinates);
    void setPlayer(PlayerType player);
    void setIsDead(bool isDead);
    void setUnicode(wchar_t unicode);

    std::vector<Point> getPossibleMoves(std::vector<Piece> otherPieces);    
private:
    PieceType type;
    Point coordinates;
    PlayerType player;
    bool isDead;
    wchar_t unicode;
};

wchar_t createUnicode(PieceType piece, PlayerType player);
std::vector<Point> getMovesRecursiveHelper(Piece, Point, Point, std::vector<Piece>, bool);

#endif
