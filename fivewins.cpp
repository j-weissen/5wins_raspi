#include "fivewins.h"
#include "ui_fivewins.h"
#include "game.h"
#include <QEvent>
#include <QMouseEvent>
#include <iostream>
#include <QScreen>

fiveWins::fiveWins(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::fiveWins)
{

    ui->setupUi(this);
    ui->pushButton_reset->hide();
    setupGui();

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

    qApp->installEventFilter(this);
}

Game* fiveWins::getGame()
{
    return game;
}

void fiveWins::setupGui(){
    QRect scr = qApp->primaryScreen()->geometry();
    int height1 = scr.height();
    int width1 = scr.width();
    int currheigt, currwidth;

    setFixedSize(width1, height1);

    sceneOffsetX = width1 / 20;
    sceneOffsetY = height1 / 20;

    width1 -= 2*sceneOffsetX;
    height1 -= 2*sceneOffsetY;


    currwidth = std::min(height1, width1);
    currheigt = currwidth;
    CellGUI::setSize(currwidth/15);

    sceneOffsetX += width1/2 - currwidth/2;
    ui->graphicsView->setGeometry(sceneOffsetX, sceneOffsetY, currwidth, currheigt);

    currheigt = sceneOffsetY;
    ui->label_turn->setGeometry(sceneOffsetX, sceneOffsetY/10, currwidth, currheigt);

    currheigt = sceneOffsetY;
    ui->message->setGeometry(sceneOffsetX, sceneOffsetY + height1, currwidth, currheigt);

    currheigt = sceneOffsetY - height()/40;
    currwidth = width()/18;
    ui->pushButton_exit_menu->setGeometry(sceneOffsetX, sceneOffsetY + height1 + currheigt/2, currwidth, currheigt);
    ui->pushButton_exit_menu->setStyleSheet("QPushButton {font: bold;}");
    ui->pushButton_reset->setGeometry(sceneOffsetX + std::min(width1, height1) - currwidth, sceneOffsetY + height1 + currheigt/2, currwidth, currheigt);
    ui->pushButton_reset->setStyleSheet("QPushButton {font: bold;}");
}

fiveWins::~fiveWins()
{
    delete game;
    delete scene;
    delete ui;
}

bool fiveWins::eventFilter(QObject *watched, QEvent *event)
{
    if (!this->isHidden() && this->isActiveWindow() && event->type() == QEvent::MouseButtonPress){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::LeftButton && game->currPlayer->type == TYPE_HUMAN && !game->getWin() && !game->getTie()){
            int x = (mouseEvent->position().x() - sceneOffsetX)/CellGUI::getSize();
            int y = (mouseEvent->position().y() - sceneOffsetY)/CellGUI::getSize();

            if (Field::inArea(x, y) && game->field->area[Field::accessArr2D(x, y)]->state == SYMBOL_FREE){ //click is in the field
                game->field->area[Field::accessArr2D(x, y)]->clicked();
                game->inputHuman(x, y);

                if (game->getWin()){
                    QString out = "Spieler ";
                    out.append(game->currPlayer->toChar());
                    out += " hat gewonnen!";

                    ui->message->setText(out);

                    io->setPlainText(out);
                    for (auto brumm : game->field->area){
                        brumm->stackBefore(io);
                    }
                    io->show();
                    ui->pushButton_reset->show();
                }else if (game->getTie()){
                    ui->message->setText("Es ist ein Unentschieden");
                    ui->pushButton_reset->show();
                }


            }else { //out of field
                if (event->type() == QEvent::Quit){
                    resetGame();
                    m->show();
                    this->close();
                    return true;
                }else{
                    return QObject::eventFilter(watched, event);
                }
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

void fiveWins::setMenu(QWidget *m)
{
    this->m = m;
}


void fiveWins::on_pushButton_reset_clicked()
{
    resetGame();
    ui->pushButton_reset->hide();
}

void fiveWins::on_pushButton_exit_menu_clicked()
{
    resetGame();
    m->show();
    this->close();
}

