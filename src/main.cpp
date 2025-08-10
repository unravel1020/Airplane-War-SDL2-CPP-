#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Game.h"

int main(int, char**) {
    Game& game = Game::getInstance();
    game.init();
    game.run();
    game.clean();

    return 0;
}