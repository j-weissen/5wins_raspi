//
// Created by maile on 07.10.2020.
//

#ifndef INC_5WINS_RASPI_GAME_H
#define INC_5WINS_RASPI_GAME_H

#include "Field.h"

class Game {
public:
    explicit Game(symbol currPlayer);
    symbol currPlayer;

private:
    void switchTurn();
    void turn();
};

#endif //INC_5WINS_RASPI_GAME_H