#include "player.h"

Player::Player(symbol playerSymbol, playerType type) : playerSymbol(playerSymbol), type(type) {}

bool Player::operator==(Player *p) const {
    return (playerSymbol == p->playerSymbol);
}

char Player::toChar() const {
    return (playerSymbol == SYMBOL_X) ? 'X' : 'O';
}

QString Player::getOutput()
{
    QString out = "Spieler ";
    out.append(toChar());
    out += " ist am Zug.";

    return out;
}
