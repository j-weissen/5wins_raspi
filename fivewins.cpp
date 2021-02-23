#include "fivewins.h"
#include "ui_fivewins.h"
#include <QtDebug>

fiveWins::fiveWins(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::fiveWins)
{

    ui->setupUi(this);


    scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);

    startGame();
}

fiveWins::~fiveWins()
{
    delete ui;
}

void fiveWins::startGame()
{
    Game game(SYMBOL_X, TYPE_HUMAN, TYPE_HUMAN, ui->message, scene);
        bool win = false;

        while (!win) {
            game.turn(&win);
        }

        QString output = "Player \"";
        output += game.currPlayer->toChar();
        output += "\" has won!";

         ui->message->setText(output);

}
