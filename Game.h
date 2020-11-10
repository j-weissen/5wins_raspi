//
// Created by maile on 07.10.2020.
//

#ifndef INC_5WINS_RASPI_GAME_H
#define INC_5WINS_RASPI_GAME_H

#include "Field.h"
#include "Player.h"


class Game {
public:
    Player *currPlayer;
    Field field;

    void turn(bool *win);
    Game(symbol startPlayer, playerType typePlayerX, playerType typePlayerO);
    ~Game();

private:
    Player *playerX;
    Player *playerO;

    int xIn, yIn;

    void switchCurrPlayer();

    void inputHuman();
    void inputAI();
};

#endif //INC_5WINS_RASPI_GAME_H