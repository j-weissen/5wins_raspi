#ifndef PLAYER_H
#define PLAYER_H

#include "Cell.h"
#include <QString>

enum playerType {
    TYPE_HUMAN, TYPE_AI, TYPE_REMOTE
};


class Player {
public:
    symbol playerSymbol;
    playerType type;

    Player(symbol playerSymbol, playerType type);
    bool operator==(Player *p) const;

    char toChar() const;
    QString getOutput();
};


#endif // PLAYER_H
