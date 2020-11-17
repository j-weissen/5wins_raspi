#include "game.h"
#include "Game.h"
#include <iostream>

Game::Game(symbol startPlayer, playerType typePlayerX, playerType typePlayerO) {
    Field();
    playerX = new Player(SYMBOL_X, typePlayerX);
    playerO = new Player(SYMBOL_O, typePlayerO);
    currPlayer = (startPlayer == SYMBOL_X) ? playerX : playerO;
}

Game::~Game() {
    delete playerX;
    delete playerO;

}

void Game::switchCurrPlayer() {
    currPlayer = (currPlayer == playerX) ? playerO : playerX;
}

void Game::turn(bool *win) {

    (currPlayer->type == TYPE_HUMAN) ? inputHuman() : inputAI();

    field.area[Field::accessArr2D(xIn, yIn)]->state = currPlayer->playerSymbol;

    *win = field.checkWin(xIn, yIn, currPlayer->playerSymbol);

    if (!*win) {
        switchCurrPlayer();
    }

    field.print();
}

void Game::inputHuman() {
    bool isFree = true;

    do {
        if (!isFree) {
            std::cout << "Choose an empty field!" << std::endl;
        }
        std::cout << "Spieler " << currPlayer->toChar() << ", Row: " << std::endl;
        std::cin >> yIn;
        std::cout << "Spieler " << currPlayer->toChar() << ", Collumn: " << std::endl;
        std::cin >> xIn;
        if (Field::inArea(xIn) && Field::inArea(yIn)) {
            isFree = field.area[Field::accessArr2D(xIn, yIn)]->state == SYMBOL_FREE;
        } else {
            isFree = false;
        }
    } while (!isFree);
}

void Game::inputAI() {

}
