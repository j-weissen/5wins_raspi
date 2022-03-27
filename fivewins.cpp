#include "fivewins.h"
#include "ui_fivewins.h"
#include "game.h"
#include <QEvent>
#include <QMouseEvent>
#include <iostream>
#include <QScreen>
#include <QSizePolicy>
#include "network/NetworkTcpClient.h"
#include "network/NetworkTcpServer.h"

QString fiveWins::messageSeparator = "#";
QString fiveWins::textSeparator = ";";


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

    socket = nullptr;
    isServer = false;

    game = nullptr;

    qApp->installEventFilter(this);
}


void fiveWins::initGame() {
    if (socket == nullptr) {
        game = new Game(SYMBOL_X, TYPE_HUMAN, TYPE_HUMAN, ui->label_turn, scene);
    } else if (isServer) {
        game = new Game(SYMBOL_X, TYPE_REMOTE, TYPE_HUMAN, ui->label_turn, scene);
        connect(socket, &Network::dataRecieved, this, &fiveWins::onDataRecieved);
    } else {
        game = new Game(SYMBOL_X, TYPE_HUMAN, TYPE_REMOTE, ui->label_turn, scene);
        connect(socket, &Network::dataRecieved, this, &fiveWins::onDataRecieved);
    }
    ui->label_turn->setText(game->currPlayer->getOutput());
}

Game* fiveWins::getGame() {
    return game;
}

void fiveWins::setupGui() {
    QRect scr = qApp->primaryScreen()->geometry();
    setFixedSize(scr.width(), scr.height());

    this->show();

    int height1 = ui->graphicsView->height();
    int width1 = ui->graphicsView->width();
    int maxSize;
    QPoint uiCords = ui->graphicsView->mapToGlobal(ui->graphicsView->pos());

    this->hide();

    sceneOffsetX = uiCords.x();
    sceneOffsetY = uiCords.y();

    maxSize = std::min(height1, width1);
    ui->graphicsView->setFixedHeight(maxSize);
    ui->graphicsView->setFixedWidth(maxSize);
    QString cssGreen = "QPushButton { background-color: rgb(89,201,38); border-style: double; border-width: 10px; border-radius: 10px; border-color: rgb(38,201,69); font: bold; min-width: 10em; } QPushButton:hover {border-color: rgb(38,131,69)}";
    QString cssRed = "QPushButton { background-color: rgb(201,44,44); border-style: double; border-width: 10px; border-radius: 10px; border-color: rgb(180,44,44); font: bold; min-width: 10em; } QPushButton:hover {border-color: rgb(100,44,44)}";

    ui->pushButton_exit_menu->setStyleSheet(cssRed);
    ui->pushButton_undo->setStyleSheet(cssGreen);
    ui->pushButton_reset->setStyleSheet(cssGreen);

    CellGUI::setSize(maxSize/15);
}

fiveWins::~fiveWins()
{
    delete game;
    delete scene;
    delete ui;
}

bool fiveWins::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress || event->type() == DataRecievedEvent::getEventType()) {

        int x, y;
        bool turnInitialized = false;


        if (event->type() == DataRecievedEvent::getEventType()) {
            DataRecievedEvent *dre = static_cast<DataRecievedEvent *>(event);

            if (dre->getAction() == DataRecievedEvent::ACTION_TURN && game->currPlayer->type == TYPE_REMOTE) {
                x = dre->getX();
                y = dre->getY();
                turnInitialized = true;
            } else if (dre->getAction() == DataRecievedEvent::ACTION_RESET) {
                reset();
            } else if (dre->getAction() == DataRecievedEvent::ACTION_EXIT) {
                exit();
            } else if (dre->getAction() == DataRecievedEvent::ACTION_UNDO){
                undo();
            } else {
                qDebug() << "Error: dre.action = " << dre->getAction();
            }
        }

        if (game != nullptr && !game->getWin() && !game->getTie()){
            if (game->currPlayer->type == TYPE_HUMAN && !this->isHidden() && this->isActiveWindow() && event->type() == QEvent::MouseButtonPress && std::strcmp(watched->metaObject()->className(), "fiveWins") == 0) {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

                if (mouseEvent->button() == Qt::LeftButton) {
                    QPoint currClick = ui->graphicsView->mapFromGlobal(mouseEvent->pos());
                    x = currClick.x()/CellGUI::getSize();
                    y = currClick.y()/CellGUI::getSize();
                    turnInitialized = true;
                }
            }
        }


        if (turnInitialized) {
            if (Field::inArea(x, y)) { // in Field
                if (game->field->area[Field::accessArr2D(x, y)]->state == SYMBOL_FREE) {

                    if (game->currPlayer->type == TYPE_HUMAN && sendUpdates()) {
                       socket->send(encodeTurn(x, y));
                    }

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
                        ui->pushButton_undo->hide();
                        ui->pushButton_reset->show();
                    }else if (game->getTie()){
                        ui->message->setText("Es ist ein Unentschieden");
                        ui->pushButton_undo->hide();
                        ui->pushButton_reset->show();
                    }
                } else { //out of field
                    if (event->type() == QEvent::Quit){
                        endGame();
                        m->show();
                        this->close();
                        return true;
                    }
                }
            }
        }
    }
    return QObject::eventFilter(watched, event);
}


void fiveWins::endGame ()
{
    delete game;
    game = nullptr;
    CellGUI::curr = 0;

    io->hide();

    playedGames++;
    ui->message->setText("Gespielte Spiele: " + QString::number(playedGames));
    ui->pushButton_reset->hide();
    ui->pushButton_undo->show();
}

void fiveWins::setMenu(QWidget *m)
{
    this->m = m;
}


void fiveWins::on_pushButton_reset_clicked()
{
    if (sendUpdates()) {
        socket->send(encodeAction(DataRecievedEvent::ACTION_RESET));
    }
    reset();
}

void fiveWins::reset() {
    endGame();
    initGame();
    ui->pushButton_reset->hide();
}

void fiveWins::on_pushButton_exit_menu_clicked()
{
    if (sendUpdates()) {
        socket->send(encodeAction(DataRecievedEvent::ACTION_EXIT));
    }
    exit();
}


void fiveWins::exit() {
    endGame();
    if (socket != nullptr) {
        socket->close();
    }
    socket = nullptr;
    emit resetSockets();
    this->close();
    m->show();
}

void fiveWins::onDataRecieved() {
    QString data = socket->getRecvData();
    QApplication::sendEvent(this, decodeDataToEvent(data));
}

DataRecievedEvent* fiveWins::decodeDataToEvent(QString data) {
    DataRecievedEvent *rv = nullptr;
    int action = data.split(textSeparator)[0].toInt();
    if (action == DataRecievedEvent::ACTION_TURN) {
        int x = data.split(textSeparator)[1].toInt();
        int y = data.split(textSeparator)[2].toInt();
        rv = new DataRecievedEvent(x, y);
    } else {
        rv = new DataRecievedEvent(action);
    }
    return rv;
}

bool fiveWins::sendUpdates() {
    return (game->currPlayer->type == TYPE_REMOTE || game->getOtherPlayerType() == TYPE_REMOTE);
}

QString fiveWins::encodeTurn(int x, int y) {
    return QString::number(DataRecievedEvent::ACTION_TURN) + textSeparator + QString::number(x) + textSeparator + QString::number(y);
}

QString fiveWins::encodeAction(int action) {
    return QString::number(action) + textSeparator;
}

Network *fiveWins::getSocket() {
    return socket;
}

void fiveWins::setSocket(Network *socket) {
    this->socket = socket;
}

void fiveWins::setIsServer(bool isServer) {
    this->isServer = isServer;
}


void fiveWins::on_pushButton_undo_clicked()
{
    undo();
}

void fiveWins::undo(){
    if (game->undo() && sendUpdates()){
        socket->send(encodeAction(DataRecievedEvent::ACTION_UNDO));
    }

}
