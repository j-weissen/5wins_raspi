#include "game.h"
#include <iostream>


Game::Game(symbol startPlayer, playerType typePlayerX, playerType typePlayerO, QLabel *message, QGraphicsScene *scene) {
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
}

void Game::switchCurrPlayer() {
    currPlayer = (currPlayer == playerX) ? playerO : playerX;
}

void Game::turn(bool *win) {

    (currPlayer->type == TYPE_HUMAN) ? inputHuman() : inputAI();

    field->area[Field::accessArr2D(xIn, yIn)]->state = currPlayer->playerSymbol;

    *win = field->checkWin(xIn, yIn, currPlayer->playerSymbol);

    if (!*win) {
        switchCurrPlayer();
    }

    scene->update();
    //field->print();
}

void Game::inputHuman() {
    bool debugWrote = false;
    CellGUI::clickable = true;
    QString out = "Spieler ";
    out.append(currPlayer->toChar());
    out += " ist am Zug.";
    message->setText(out);
    while (CellGUI::clickable) {
        if (!debugWrote){
            qDebug() << "Human Move\n";
            debugWrote = true;
        }

    }
}

void Game::inputAI() {

}
