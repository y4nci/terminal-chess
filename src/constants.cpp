#include "constants.h"

std::unordered_map<int, struct UNIT_MOVE> UNIT_MOVES = {
    { EMPTY_PIECE, { { Point (0, 0) }, false } },
    { PAWN, { { Point (1, 0) }, false } },
    { KNIGHT, { { Point (2, 1), Point (1, 2), Point (-2, 1), Point (1, -2), Point (-1, 2), Point (2, -1), Point (-2, -1), Point (-1, -2) }, false } },
    { BISHOP, { { Point (1, 1), Point (-1, 1), Point (1, -1), Point (-1, -1) }, true } },
    { ROOK, { { Point (1, 0), Point (0, 1), Point (-1, 0), Point (0, -1) }, true } },
    { QUEEN, { { Point(1, 0), Point (-1, 0), Point (1, 1), Point (-1, 1), Point (1, -1), Point (-1, -1), Point (0, 1), Point (0, -1) }, true } },
    { KING, { { Point(1, 0), Point (-1, 0), Point (1, 1), Point (-1, 1), Point (1, -1), Point (-1, -1), Point (0, 1), Point (0, -1) }, false } }
};

std::unordered_map<int, wchar_t> BLACK_PIECES = {
    { EMPTY_PIECE, L' ' },
    { PAWN, L'♙' },
    { KNIGHT, L'♘' },
    { BISHOP, L'♗' },
    { ROOK, L'♖' },
    { QUEEN, L'♕' },
    { KING, L'♔' }
};

std::unordered_map<int, wchar_t> WHITE_PIECES = {
    { EMPTY_PIECE, L' ' },
    { PAWN, L'♟' },
    { KNIGHT, L'♞' },
    { BISHOP, L'♝' },
    { ROOK, L'♜' },
    { QUEEN, L'♛' },
    { KING, L'♚' }
};

std::vector<std::wstring> CHESS_BOARD = {
    (std::wstring) L"   a   b   c   d   e   f   g   h   ",
    (std::wstring) L" ╔═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╗ ",
    (std::wstring) L"8║   ║   ║   ║   ║   ║   ║   ║   ║8",
    (std::wstring) L" ╠═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣ ",
    (std::wstring) L"7║   ║   ║   ║   ║   ║   ║   ║   ║7",
    (std::wstring) L" ╠═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣ ",
    (std::wstring) L"6║   ║   ║   ║   ║   ║   ║   ║   ║6",
    (std::wstring) L" ╠═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣ ",
    (std::wstring) L"5║   ║   ║   ║   ║   ║   ║   ║   ║5",
    (std::wstring) L" ╠═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣ ",
    (std::wstring) L"4║   ║   ║   ║   ║   ║   ║   ║   ║4",
    (std::wstring) L" ╠═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣ ",
    (std::wstring) L"3║   ║   ║   ║   ║   ║   ║   ║   ║3",
    (std::wstring) L" ╠═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣ ",
    (std::wstring) L"2║   ║   ║   ║   ║   ║   ║   ║   ║2",
    (std::wstring) L" ╠═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣ ",
    (std::wstring) L"1║   ║   ║   ║   ║   ║   ║   ║   ║1",
    (std::wstring) L" ╚═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╝ ",
    (std::wstring) L"   a   b   c   d   e   f   g   h   "
};

