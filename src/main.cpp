#include "Controllers.h"

#include <locale.h>

int main() {
    setlocale(LC_ALL, "");
    
    GameController gameController;

    gameController.startGame();

    return 0;
}
