//
// Created by maile on 07.10.2020.
//

#ifndef INC_5WINS_RASPI_GAME_H
#define INC_5WINS_RASPI_GAME_H

#include "Field.h"

enum player{human,ai};

class Game {
public:
    symbol currPlayer;
    Field field;

    void turn(bool *win);

    explicit Game(symbol currPlayer);

private:
    player px = human;
    player po = human;
    int xIn, yIn;
    void switchTurn();
    void inputHuman();
    void inputAI();
};

#endif //INC_5WINS_RASPI_GAME_H