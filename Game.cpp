//
// Created by maile on 07.10.2020.
//

#include "Game.h"


Game::Game(symbol currPlayer) : currPlayer(currPlayer) {}


void Game::turn() {

}

void Game::switchTurn() {
    if (currPlayer == x) {
        currPlayer = o;
    } else {
        currPlayer = x;
    }
}

