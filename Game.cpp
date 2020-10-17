//
// Created by maile on 07.10.2020.
//

#include "Game.h"
#include <iostream>

Game::Game(symbol currPlayer) : currPlayer(currPlayer) {}

void Game::switchTurn() {
    currPlayer = (currPlayer == x) ? o : x;
}

void Game::turn() {
    int xIn, yIn;
    Field field;

    // Input
    std::cout << "Spieler " << currPlayer << ", Row: " << std::endl;
    std::cin >> yIn;
    std::cout << "Spieler " << currPlayer << ", Collumn: " << std::endl;
    std::cin >> xIn;

    field.area[Field::accessArr2D(xIn, yIn)]->state = currPlayer;

    if (field.area[0]->state != field.area[1]->state) {
        std::cout << "MEGA NEGA";
    }
}