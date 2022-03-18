#include "fivewins.h"
#include "ui_fivewins.h"
#include "game.h"
#include <QEvent>
#include <QMouseEvent>
#include <iostream>
#include "network/NetworkTcpClient.h"
#include "network/NetworkTcpServer.h"
#include "network/dataRecievedEvent.h"

QString fiveWins::messageSeparator = "#";
QString fiveWins::textSeparator = ";";
int fiveWins::port = 12345;

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

    socket = nullptr;


    qApp->installEventFilter(this);

//    DataRecievedEvent *dre = new DataRecievedEvent(1337, 0);
//    QApplication::sendEvent(this, dre);
}


// TODO connect(socket, &Network::dataRecieved, this, &fiveWins::onDataRecieved)
/* TODO: instanciate Game dependong on game type
void fiveWins::setupGame(playerType playerX, playerType playerO) {

    game = new Game(SYMBOL_X, playerX, playerO, ui->label_turn, scene);
}
*/
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
    currwidth = width()/20;
    ui->pushButton_exit_menu->setGeometry(sceneOffsetX, sceneOffsetY + height1 + currheigt/2, currwidth, currheigt);
    ui->pushButton_exit_menu->setStyleSheet("QPushButton {font: bold " + QString::number(std::max(currwidth/7, 1)) + "px;}");
    ui->pushButton_reset->setGeometry(sceneOffsetX + std::min(width1, height1) - currwidth, sceneOffsetY + height1 + currheigt/2, currwidth, currheigt);
    ui->pushButton_reset->setStyleSheet("QPushButton {font: bold " + QString::number(std::max(currwidth/7, 1)) + "px;}");
}

fiveWins::~fiveWins()
{
    delete game;
    delete scene;
    delete ui;
}

bool fiveWins::eventFilter(QObject *watched, QEvent *event)
{
    // TODO: Handling Event based on player type
    if (event->type() == DataRecievedEvent::getEventType()) {
        DataRecievedEvent *dre = static_cast<DataRecievedEvent *>(event);
        qDebug() << "x: " << QString::number(dre->getX());
        game->inputHuman(dre->getX(), dre->getY());

    }

    if (!this->isHidden() && this->isActiveWindow() && event->type() == QEvent::MouseButtonPress){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::LeftButton && game->currPlayer->type == TYPE_HUMAN && !game->getWin() && !game->getTie()){
            int x = (mouseEvent->position().x() - sceneOffsetX)/CellGUI::getSize();
            int y = (mouseEvent->position().y() - sceneOffsetY)/CellGUI::getSize();

            if (Field::inArea(x, y) && game->field->area[Field::accessArr2D(x, y)]->state == SYMBOL_FREE){ //click is in the field
                game->field->area[Field::accessArr2D(x, y)]->clicked();
                game->inputHuman(x, y);

                QString encoded = QString::number(x) + QString::number(y);
                socket->send(encoded);

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

void fiveWins::onDataRecieved() {
    QString data = socket->getRecvData();
    int x = data.split(textSeparator)[0].toInt();
    int y = data.split(textSeparator)[1].toInt();
    DataRecievedEvent *dre = new DataRecievedEvent(x, y);
    QApplication::sendEvent(this, dre);
}

Network *fiveWins::getSocket() {
    return socket;
}



