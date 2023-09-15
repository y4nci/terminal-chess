#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include "models/Board.h"
#include "constants.h"
#include "models/Piece.h"
#include "models/Point.h"
#include "types.h"

#include <functional>
#include <ncursesw/ncurses.h>
#include <vector>

class GameController;

class InputController {
public:
    InputController();
    InputController(
        std::function<void(GameController&, Point)> moveCursor,
        std::function<void(GameController&, bool)> selectPieceAtCursor,
        std::function<void(GameController&)> moveSelectedToCursor,
        std::function<void(GameController&)> quit
    );
    ~InputController();

    void start(GameController&);

    InputController operator=(InputController& other);
private:
    std::function<void(GameController&, Point)> moveCursor;
    std::function<void(GameController&, bool)> selectPieceAtCursor;
    std::function<void(GameController&)> moveSelectedToCursor;
    std::function<void(GameController&)> quit;
};

class GameController {
public:
    GameController();
    ~GameController();

    void startGame();
private:
    Board board;
    std::vector<Piece> pieces;
    InputController inputController;

    void initUI();
    void display();
    void moveCursor(Point);
    void selectPieceAtCursor(bool);
    void moveSelectedToCursor();
    void quit();
};

#endif
