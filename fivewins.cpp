#include "fivewins.h"
#include "ui_fivewins.h"
#include "game.h"
#include <QEvent>
#include <QMouseEvent>

fiveWins::fiveWins(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::fiveWins)
{

    ui->setupUi(this);
    ui->pushButton_reset->hide();

    scene = new QGraphicsScene(this);

    playedGames = 0;


    QFont font;
    font.setBold(true);
    font.setPixelSize(60);


    io = new QGraphicsTextItem;
    io->setDefaultTextColor(Qt::blue);
    io->setPos(0, 0);
    io->setFont(font);

    scene->addItem(io);

    ui->graphicsView->setScene(scene);

    game = new Game(SYMBOL_X, TYPE_HUMAN, TYPE_HUMAN, ui->label_turn, scene);
    for (auto brumm : game->field->area){
        brumm->stackBefore(io);
    }
    qApp->installEventFilter(this);
    showMaximized();
}

fiveWins::~fiveWins()
{
    delete game;
    delete scene;
    delete ui;
}

bool fiveWins::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress){

        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::LeftButton && game->currPlayer->type == TYPE_HUMAN && !game->getWin() && !game->getTie()){
            int x = (mouseEvent->x() - SCENE_OFFSET)/CellGUI::SIZE;
            int y = (mouseEvent->y() - SCENE_OFFSET)/CellGUI::SIZE;

            if (Field::inArea(x) && Field::inArea(y)){ //click is in the field
                game->field->area[Field::accessArr2D(x, y)]->clicked();
                game->inputHuman(x, y);

                if (game->getWin()){
                    QString out = "Spieler ";
                    out.append(game->currPlayer->toChar());
                    out += " hat gewonnen!";

                    ui->message->setText(out);

                    io->setPlainText(out);
                    io->show();
                }

                ui->pushButton_reset->show();
            }else if (game->getTie()){
                ui->message->setText("Es ist ein Unentschieden");
            }

        }else if (mouseEvent->button() == Qt::LeftButton && (game->getWin() || game->getTie())){
            return QObject::eventFilter(watched, event);
        }
        return true;
    }
    return QObject::eventFilter(watched, event);
}

void fiveWins::resetGame()
{
    delete game;
    game = new Game(SYMBOL_X, TYPE_HUMAN, TYPE_HUMAN, ui->label_turn, scene);
    CellGUI::curr = 0;

    ui->label_turn->setText(game->currPlayer->getOutput());
    io->hide();

    playedGames++;

    ui->message->setText("Gespielte Spiele: " + QString::number(playedGames));
}


void fiveWins::on_pushButton_reset_clicked()
{
    resetGame();
    ui->pushButton_reset->hide();
}
