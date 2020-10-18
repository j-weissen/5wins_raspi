//
// Created by maile on 07.10.2020.
//

#ifndef INC_5WINS_RASPI_GAME_H
#define INC_5WINS_RASPI_GAME_H

#include "Field.h"

class Game {
public:
    symbol currPlayer;
    Field field;

    void turn(bool *win);

    explicit Game(symbol currPlayer);

private:
    void switchTurn();

};

#endif //INC_5WINS_RASPI_GAME_H