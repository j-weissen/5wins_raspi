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
    void inputHuman(int x, int y);
    bool getWin();
    bool getTie();
    void reset();
    playerType getOtherPlayerType();
    Game(symbol startPlayer, playerType typePlayerX, playerType typePlayerO, QLabel *message, QGraphicsScene *scene);
    ~Game();

private:
    Player *playerX;
    Player *playerO;

    int xIn, yIn;
    bool win;
    bool tie;

    void switchCurrPlayer();

    void inputAI();
};

#endif // GAME_H
