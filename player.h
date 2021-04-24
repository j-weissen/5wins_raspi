#ifndef PLAYER_H
#define PLAYER_H

#include "cell.h"
#include <QString>

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
    QString getOutput();
};


#endif // PLAYER_H
