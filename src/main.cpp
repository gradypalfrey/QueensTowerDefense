#include <iostream>
#include "Game.h"

void loadTextures(std::map <std::string, sf::Texture>&  m){
    // CALL THIS TO LOAD ALL THE TEXTURES
}

int main() {

    // Create the game
    Game game;
    srand(time(NULL));

    while (game.running()) {
        switch(game.getMode()) {
            case menu:
                game.gameMenu();
                break;
            case play:
                game.update();
                game.render();
                break;
            case gameover:
                game.gameOver();
                break;
        }
    }
    return 0;
}