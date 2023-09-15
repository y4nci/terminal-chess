#include "Controllers.h"

GameController::GameController() {
    std::vector<Piece> chessPieces;

    for (int i = 0; i < 8; i++) {
        Piece pawn (PieceType::PAWN, Point (6, i), PlayerType::WHITE);
        chessPieces.push_back(pawn);
    }

    for (int i = 0; i < 8; i++) {
        Piece pawn (PieceType::PAWN, Point (1, i), PlayerType::BLACK);
        chessPieces.push_back(pawn);
    }

    chessPieces.push_back(Piece (PieceType::ROOK, Point (7, 0), PlayerType::WHITE));
    chessPieces.push_back(Piece (PieceType::ROOK, Point (7, 7), PlayerType::WHITE));

    chessPieces.push_back(Piece (PieceType::ROOK, Point (0, 0), PlayerType::BLACK));
    chessPieces.push_back(Piece (PieceType::ROOK, Point (0, 7), PlayerType::BLACK));

    chessPieces.push_back(Piece (PieceType::KNIGHT, Point (7, 1), PlayerType::WHITE));
    chessPieces.push_back(Piece (PieceType::KNIGHT, Point (7, 6), PlayerType::WHITE));

    chessPieces.push_back(Piece (PieceType::KNIGHT, Point (0, 1), PlayerType::BLACK));
    chessPieces.push_back(Piece (PieceType::KNIGHT, Point (0, 6), PlayerType::BLACK));

    chessPieces.push_back(Piece (PieceType::BISHOP, Point (7, 2), PlayerType::WHITE));
    chessPieces.push_back(Piece (PieceType::BISHOP, Point (7, 5), PlayerType::WHITE));

    chessPieces.push_back(Piece (PieceType::BISHOP, Point (0, 2), PlayerType::BLACK));
    chessPieces.push_back(Piece (PieceType::BISHOP, Point (0, 5), PlayerType::BLACK));

    chessPieces.push_back(Piece (PieceType::QUEEN, Point (7, 3), PlayerType::WHITE));
    chessPieces.push_back(Piece (PieceType::QUEEN, Point (0, 4), PlayerType::BLACK));

    chessPieces.push_back(Piece (PieceType::KING, Point (7, 4), PlayerType::WHITE));
    chessPieces.push_back(Piece (PieceType::KING, Point (0, 3), PlayerType::BLACK));

    this->pieces = chessPieces;

    Board chessBoard = Board (this->pieces);

    this->board = chessBoard;

    InputController inputCtr = InputController (
        [this](GameController&, Point direction) { this->moveCursor(direction); },
        [this](GameController&, bool select) { this->selectPieceAtCursor(select); },
        [this](GameController&) { this->moveSelectedToCursor(); },
        [this](GameController&) { this->quit(); }
    );

    this->inputController = inputCtr;

    this->initUI();
}

GameController::~GameController() {
    // TODO: here
    endwin();
}

void GameController::initUI() {
    initscr();
    start_color();

    init_pair(Colouring::POSSIBLE_MOVE, COLOR_RED, COLOR_BLACK);
    init_pair(Colouring::SELECTED, COLOR_YELLOW, COLOR_BLACK);

    mvprintw(0, 0, "Hello! Press any key to start the game.");
}

void GameController::startGame() {
    this->inputController.start(*this);
}

void GameController::display() {
    this->board.display();
    refresh();
}

void GameController::moveCursor(Point direction) {
    this->board.setCursor(this->board.getCursor() + direction);
    this->display();
}

void GameController::selectPieceAtCursor(bool select) {
    this->board.selectPieceAtCursor(select);
    this->display();
}

void GameController::moveSelectedToCursor() {
    this->board.moveSelectedToCursor();
    this->display();
}

void GameController::quit() {
    this->~GameController();
}

InputController::InputController() { }

InputController::InputController(
    std::function<void(GameController&, Point)> moveCursor,
    std::function<void(GameController&, bool)> selectPieceAtCursor,
    std::function<void(GameController&)> moveSelectedToCursor,
    std::function<void(GameController&)> quit
): moveCursor(moveCursor), selectPieceAtCursor(selectPieceAtCursor), moveSelectedToCursor(moveSelectedToCursor), quit(quit) { }

InputController::~InputController() { }

void InputController::start(GameController& gameController) {
    int input;

    while (true) {
        input = getch();

        switch (input) {
            case 'w':
                this->moveCursor(gameController, Point (-1, 0));
                break;
            case 's':
                this->moveCursor(gameController, Point (1, 0));
                break;
            case 'a':
                this->moveCursor(gameController, Point (0, -1));
                break;
            case 'd':
                this->moveCursor(gameController, Point (0, 1));
                break;
            case ' ':
                this->selectPieceAtCursor(gameController, true);
                break;
            case 'u':
                this->selectPieceAtCursor(gameController, false);
                break;
            case 'q':
                this->quit(gameController);
                break;
            case '\n':
                this->moveSelectedToCursor(gameController);
                break;
            default:
                break;
        }
    }
}

InputController InputController::operator=(InputController& other) {
    this->moveCursor = other.moveCursor;
    this->selectPieceAtCursor = other.selectPieceAtCursor;
    this->moveSelectedToCursor = other.moveSelectedToCursor;
    this->quit = other.quit;

    return *this;
}
