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

    void turn(bool *win, bool *tie);
    Game(symbol startPlayer, playerType typePlayerX, playerType typePlayerO);
    ~Game();

private:
    Player *playerX;
    Player *playerO;

    int xIn, yIn;

    int aiBestScore = INT32_MIN;
    int humanBestScore = INT32_MAX;

    Field aiTestField;

    void switchCurrPlayer();

    void inputHuman();
    void inputAI();

    int aiMinimax(int depth, bool isMaximizing, symbol identity, int tempX, int tempY);
};

#endif //INC_5WINS_RASPI_GAME_H