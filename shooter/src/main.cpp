#include "shooter/Game.h"

int main(int /*argc*/, char ** /*args[]*/) {
    Game &game = Game::getInstance();
    game.initGame();
    game.runGame();

    return 0;
}