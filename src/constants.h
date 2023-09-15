#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "models/Point.h"
#include <string>
#include "types.h"

#include <unordered_map>
#include <vector>

/**
 * @brief A map of all the possible moves for each white piece type.
 * Note that the white is in the bottom of the screen, so the pawns go up only. as a result, white pawns should be multiplied with a scalar -1.
 */
extern std::unordered_map<int, struct UNIT_MOVE> UNIT_MOVES;

extern std::unordered_map<int, wchar_t> WHITE_PIECES;

extern std::unordered_map<int, wchar_t> BLACK_PIECES;

extern std::vector<std::wstring> CHESS_BOARD;

#endif
