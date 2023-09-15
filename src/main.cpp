#include "Controllers.h"

#include <locale.h>

int main() {
    setlocale(LC_ALL, "");
    
    GameController gameController = GameController ();
    InputController inputController = InputController ();

    gameController.startGame();

    return 0;
}
