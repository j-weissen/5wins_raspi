#ifndef GAME_H
#define GAME_H

#include "field.h"
#include "player.h"
#include <QLabel>

class Game {
public:
    Player *currPlayer;
    Field *field;
    QLabel *message;
    QGraphicsScene *scene;

    void turn(bool *win);
    Game(symbol startPlayer, playerType typePlayerX, playerType typePlayerO, QLabel *message, QGraphicsScene *scene);
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
