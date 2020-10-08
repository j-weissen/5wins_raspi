//
// Created by maile on 07.10.2020.
//

#ifndef INC_5WINS_RASPI_GAME_H
#define INC_5WINS_RASPI_GAME_H

#include "Field.h"

class Game {
    void switchTurn();
private:
    void turn();
    int accessArr2D(int x, int y);
};


#endif //INC_5WINS_RASPI_GAME_H
