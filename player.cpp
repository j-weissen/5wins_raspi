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
    QString out = "";
    if (toChar() == 'X'){
        out.append("Grün");
    }else {
        out.append("Pink");
    }
    out += " ist am Zug.";

    return out;
}
