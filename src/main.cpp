#include "Controllers.h"

int main() {
    GameController gameController = GameController ();
    InputController inputController = InputController ();

    gameController.startGame();

    return 0;
}
