#ifndef TYPES_H
#define TYPES_H

#include "models/Point.h"

#include <vector>

enum PlayerType {
    EMPTY_PLAYER,
    WHITE,
    BLACK
};

enum PieceType {
    EMPTY_PIECE,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

enum Colouring {
    SELECTED = 1,
    POSSIBLE_MOVE = 2
};

struct UNIT_MOVE {
    /**
     * @brief unit moves
     */
    std::vector<Point> unitMoveVectors;

    /**
     * @brief whether the piece can perform the moves that are multiples of the vectors. false for pawn, for example.
     */
    bool multipleAllowed;
};

#endif
