#include "fivewins.h"
#include "ui_fivewins.h"

//git test

fiveWins::fiveWins(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::fiveWins)
{

    ui->setupUi(this);


    scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);

    initArea();
}

fiveWins::~fiveWins()
{
    delete ui;
}

void fiveWins::initArea()
{
    for (int i = 0; i<15 ; ++i) {
        for (int j = 0; j<15 ; ++j) {
            area[i + j*15] = new CellGUI(i, j);
            scene->addItem(area[i + j*15]);
        }
    }

}

void fiveWins::startGame()
{
    Game game(SYMBOL_X, TYPE_HUMAN, TYPE_HUMAN);
        bool win = false;

        game.field.print();

        while (!win) {
            game.turn(&win);
        }

        QString output = "Player \"";
        output += game.currPlayer->toChar();
        output += "\" has won!";

         ui->message->setText(output);

}
