//
// Created by maile on 07.10.2020.
//

#include "Game.h"
#include <iostream>

Game::Game(symbol currPlayer) : currPlayer(currPlayer) {
    field.init_Area();
}

void Game::switchTurn() {
    currPlayer = (currPlayer == x) ? o : x;
}

void Game::turn(bool *win) {
    int xIn, yIn;

    bool isfree = true;

    // Input
    do {
        if (!isfree) {
            std::cout << "Choose an empty field!" << std::endl;
        }
        std::cout << "Spieler " << currPlayer << ", Row: " << std::endl;
        std::cin >> yIn;
        std::cout << "Spieler " << currPlayer << ", Collumn: " << std::endl;
        std::cin >> xIn;
        if (!(yIn <= Field::maxArea && xIn <= Field::maxArea)) {
            isfree = field.area[Field::accessArr2D(xIn, yIn)]->state == f;
        } else {
            isfree = false;
        }
    } while (!isfree);
    field.area[Field::accessArr2D(xIn, yIn)]->state = currPlayer;

    *win = field.checkWin(xIn, yIn, currPlayer);

    if (!*win) {
        switchTurn();
    }
    field.print();
}