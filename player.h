#ifndef PLAYER_H
#define PLAYER_H

#include "cell.h"

enum playerType {
    TYPE_HUMAN, TYPE_AI
};


class Player {
public:
    symbol playerSymbol;
    playerType type;

    Player(symbol playerSymbol, playerType type);
    bool operator==(Player *p) const;

    char toChar() const;
};


#endif // PLAYER_H
