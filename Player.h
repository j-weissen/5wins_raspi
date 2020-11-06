//
// Created by maile on 06.11.2020.
//

#ifndef INC_5WINS_RASPI_PLAYER_H
#define INC_5WINS_RASPI_PLAYER_H

#include "Cell.h"

enum playerType{TYPE_HUMAN,TYPE_AI};


class Player {
private:
    symbol playerSymbol;
    playerType type;

    void inputHuman();
    void inputAI();



};


#endif //INC_5WINS_RASPI_PLAYER_H
