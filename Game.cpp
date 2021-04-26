#include "game.h"
#include <iostream>

Game::Game(symbol startPlayer, playerType typePlayerX, playerType typePlayerO, QLabel *message, QGraphicsScene *scene) {
    win = false;
    tie = false;
    field = new Field(scene);
    playerX = new Player(SYMBOL_X, typePlayerX);
    playerO = new Player(SYMBOL_O, typePlayerO);
    currPlayer = (startPlayer == SYMBOL_X) ? playerX : playerO;
    this->message = message;
    this->scene = scene;
}

Game::~Game() {
    delete playerX;
    delete playerO;
    delete field;
    delete message;
    delete scene;
}

void Game::switchCurrPlayer() {
    currPlayer = (currPlayer == playerX) ? playerO : playerX;
}

void Game::turn(bool *win) {

    (currPlayer->type == TYPE_HUMAN) ? inputHuman(-1,-1) : inputAI();

    *win = field->checkWin(xIn, yIn, currPlayer->playerSymbol);

    if (!*win) {
        switchCurrPlayer();
    }

    scene->update();
}

void Game::inputHuman(int x, int y) {
    QString out;
    field->area[Field::accessArr2D(x, y)]->state = currPlayer->playerSymbol;
    win = field->checkWin(x, y, currPlayer->playerSymbol);
    tie = field->checkTie();

    if(!win){
        switchCurrPlayer();

        message->setText(currPlayer->getOutput());
    }else if (win){
        out = "Spieler ";
        out.append(currPlayer->toChar());
        out += " hat gewonnen!";
        message->setText(out);
    }else{
        out = "Es ist ein Unentschieden";
        message->setText(out);
    }

}

bool Game::getWin()
{
    return win;
}

bool Game::getTie()
{
    return tie;
}

void Game::inputAI() {

}
