//
// Created by maile on 07.10.2020.
//

#include "Game.h"
#include <iostream>

Game::Game(symbol currPlayer) : currPlayer(currPlayer) {}

void Game::switchTurn() {
    if (currPlayer == x) {
        currPlayer = o;
    } else {
        currPlayer = x;
    }
}

void Game::turn() {
    int xIn, yIn;
    Field field;

    // Input
    std::cout << "Spieler " << currPlayer << ", Row: " << std::endl;
    std::cin >> yIn;
    std::cout << "Spieler " << currPlayer << ", Collumn: " << std::endl;
    std::cin >> xIn;

    field.area[Field::accessArr2D(xIn, yIn)].set(xIn, yIn);
}