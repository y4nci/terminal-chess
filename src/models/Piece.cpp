#include "Piece.h"

wchar_t createUnicode(PieceType piece, PlayerType player) {
    if (player == PlayerType::WHITE) {
        return WHITE_PIECES[piece];
    } else if (player == PlayerType::BLACK) {
        return BLACK_PIECES[piece];
    } else {
        return ' ';
    }
}

Piece::Piece() {
    this->type = EMPTY_PIECE;
    this->coordinates.x = 0, this->coordinates.y = 0;
    this->player = PlayerType::EMPTY_PLAYER;
    this->isDead = false;
    this->isSelected = false;
    this->unicode = ' ';
}

Piece::Piece(PieceType piece, Point coordinates, PlayerType player) {
    this->type = piece;
    this->coordinates = coordinates;
    this->player = player;
    this->isDead = false;
    this->isSelected = false;
    this->unicode = createUnicode(piece, player);
}

Piece::~Piece() {}

PieceType Piece::getType() {
    return this->type;
}

Point Piece::getCoordinates() {
    return this->coordinates;
}

PlayerType Piece::getPlayer() {
    return this->player;
}

bool Piece::getIsDead() {
    return this->isDead;
}

bool Piece::getIsSelected() {
    return this->isSelected;
}

std::wstring Piece::getUnicode() {
    return (std::wstring) { this->unicode, L'\0' };
}

void Piece::setType(PieceType piece) {
    this->type = piece;
    this->unicode = createUnicode(piece, this->player);
}

void Piece::setCoordinates(Point coordinates) {
    this->coordinates = coordinates;
}

void Piece::setPlayer(PlayerType player) {
    this->player = player;
    this->unicode = createUnicode(this->type, player);
}

void Piece::setIsDead(bool isDead) {
    this->isDead = isDead;
}

void Piece::setIsSelected(bool isSelected) {
    this->isSelected = isSelected;
}

void Piece::setUnicode(wchar_t unicode) {
    this->unicode = unicode;
}

/**
 * returns the possible moves for a chess piece
 * @param otherPieces other pieces on the board.
 * @return `std::vector<Point>` of possible moves
 */
std::vector<Point> Piece::getPossibleMoves(std::vector<Piece> otherPieces) {
    std::vector<Point> possibleMoves;
    struct UNIT_MOVE unitMove = UNIT_MOVES[this->type];

    if (this->type == EMPTY_PIECE) {
        return possibleMoves;
    } else if (this->type == PieceType::PAWN) {
        if (this->player == PlayerType::BLACK) {
            if (this->coordinates.x == 1) unitMove.unitMoveVectors.push_back(Point (0, 2));
        } else {
            if (this->coordinates.x == 6) unitMove.unitMoveVectors.push_back(Point (0, 2));

            for (int i = 0; i < unitMove.unitMoveVectors.size(); i++) {
                unitMove.unitMoveVectors[i] *= -1; 
            }
        }
    }

    for (Point unitVector : unitMove.unitMoveVectors) {
        std::vector<Point> validMoves = getMovesRecursiveHelper(this->coordinates, unitVector, otherPieces, unitMove.multipleAllowed);
        possibleMoves.insert(possibleMoves.end(), validMoves.begin(), validMoves.end());
    }

    return possibleMoves;
}

/**
 * returns the possible moves for a chess piece in the given direction. 
 * when a piece is found in the direction, or the end of the board is reached, function halts.
 * the result includes the square with the piece if and only if the piece belongs to the opponent.
 * @param pieces the vector that includes the pieces
 * @param piece the piece to be moved
 * @param moveVector the direction to move
 * @return std::vector<Point> all valid moves in the given direction
 */
std::vector<Point> getMovesRecursiveHelper(Point currentCoordinates, Point moveVector, std::vector<Piece> pieces, bool multipleAllowed) {
    std::vector<Point> possibleMoves;

    do {
        currentCoordinates += moveVector;

        if (currentCoordinates.x < 0 || currentCoordinates.x > 7 || currentCoordinates.y < 0 || currentCoordinates.y > 7) {
            break;
        }

        possibleMoves.push_back(currentCoordinates);

        for (Piece piece : pieces) {
            if (!piece.getIsDead() && piece.getType() != EMPTY_PIECE && piece.getCoordinates() == currentCoordinates) {
                if (piece.getPlayer() == piece.getPlayer()) {
                    possibleMoves.pop_back();
                }

                break;
            }
        }
    } while (multipleAllowed);

    return possibleMoves;
}
