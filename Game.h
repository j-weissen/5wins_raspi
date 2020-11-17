#ifndef GAME_H
#define GAME_H

#include "field.h"
#include "player.h"


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

#endif // GAME_H
