
#include "Game.hpp"

int main(int argc, char* argv[]) {
    auto game = new sb::Game();
    int retVal = game->run();
    delete game;
    return retVal;
}
