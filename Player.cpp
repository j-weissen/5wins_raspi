//
// Created by maile on 06.11.2020.
//

#include "Player.h"


Player::Player(symbol playerSymbol, playerType type) : playerSymbol(playerSymbol), type(type) {}

bool Player::operator==(Player *p) const {
    return (playerSymbol == p->playerSymbol);
}

char Player::toChar() const {
    return (playerSymbol == SYMBOL_X) ? 'X' : 'O';
}
