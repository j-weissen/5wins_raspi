#include "menu.h"
#include "ui_menu.h"
#include "QDir"



menu::menu(fiveWins *gameWidget, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::menu)
{
    ui->setupUi(this);
    QWidget::showFullScreen();

    //Get Screen Size/Resolution
    QRect rec = QApplication::primaryScreen()->geometry();
    static const int height = rec.height();
    static const int width = rec.width();

    //Set Text position
    ui->label_5wins->setGeometry(0, (height/2)-(height/10)*3-(height/30)*2, width, height/5);
    ui->label_5wins->setStyleSheet("QLabel {font: bold " + QString::number(width/14) + "px;}");

    //Set All Pushbutton position
    qDebug() << width;
    ui->pushButton_local2Player->setGeometry((width/2)-(width/10)/2, (height/2)-(height/10)-(height/30), width/10, height/10);

    ui->pushButton_createServer->setGeometry((width/2)-(width/10)-(width/42), (height/2), width/10, height/10);
    ui->pushButton_joinServer->setGeometry((width/2) + (width/42), (height/2), width/10, height/10);

    ui->pushButton_vsAI->setGeometry((width/2)-(width/10)/2, (height/2)+(height/10)+(height/30), width/10, height/10);
    ui->pushButton_exit->setGeometry((width/2)-(width/10)/2, (height/2)+(height/10)*2+(height/30)*2, width/10, height/10);

    //PushButton CSS for Menu
    ui->pushButton_local2Player->setStyleSheet("QPushButton { background-color: rgb(89,201,38); border-style: double; border-width: 10px; border-radius: 10px; border-color: rgb(38,201,69); font: bold " + QString::number(width/10/14) + "px; min-width: 10em; } QPushButton:hover {border-color: rgb(38,131,69)}");
    ui->pushButton_createServer->setStyleSheet("QPushButton { background-color: rgb(89,201,38); border-style: double; border-width: 10px; border-radius: 10px; border-color: rgb(38,201,69); font: bold " + QString::number(width/10/14) + "px; min-width: 10em; } QPushButton:hover {border-color: rgb(38,131,69)}");
    ui->pushButton_joinServer->setStyleSheet("QPushButton { background-color: rgb(89,201,38); border-style: double; border-width: 10px; border-radius: 10px; border-color: rgb(38,201,69); font: bold " + QString::number(width/10/14) + "px; min-width: 10em; } QPushButton:hover {border-color: rgb(38,131,69)}");
    ui->pushButton_vsAI->setStyleSheet("QPushButton { background-color: rgb(89,201,38); border-style: double; border-width: 10px; border-radius: 10px; border-color: rgb(38,201,69); font: bold " + QString::number(width/10/14) + "px; min-width: 10em; } QPushButton:hover {border-color: rgb(38,131,69)}");
    ui->pushButton_exit->setStyleSheet("QPushButton { background-color: rgb(201,44,44); border-style: double; border-width: 10px; border-radius: 10px; border-color: rgb(180,44,44); font: bold " + QString::number(width/10/14) + "px; min-width: 10em; } QPushButton:hover {border-color: rgb(100,44,44)}");

    this->gameWidget = gameWidget;
    this->gameWidget->setMenu(this);

    connect(gameWidget, &fiveWins::resetSockets, this, &menu::initNetwork);
    initNetwork();
}

menu::~menu()
{
    delete ui;
    delete server;
    delete client;
}

void menu::initNetwork() {
    server = new NetworkTcpServer(fiveWins::messageSeparator);
    client = new NetworkTcpClient(fiveWins::messageSeparator);

    QObject::connect(client, &NetworkTcpClient::connected, this, &menu::onConnected);
    QObject::connect(server, &NetworkTcpServer::connected, this, &menu::onConnected);

    ui->label_serverIp->clear();
}

void menu::on_pushButton_exit_clicked()
{
    qApp->quit();
}



void menu::on_pushButton_local2Player_clicked()
{
    gameWidget->setSocket(nullptr);
    startGame();
}

void menu::startGame() {
    gameWidget->initGame();
    if (gameWidget->getGame()->getTie() || gameWidget->getGame()->getWin()){
        gameWidget->endGame();
    }
    gameWidget->showFullScreen();
    this->close();
}

void menu::on_pushButton_createServer_clicked() {
    if (!server->isListening()) {
        gameWidget->setIsServer(true);

        QString address = server->startListening();
        ui->label_serverIp->setText(address);

        gameWidget->setSocket(server);
    }
}


void menu::on_pushButton_joinServer_clicked() {
    if (ui->lineEdit_ip->text().split(":").length() == 2) {
        gameWidget->setIsServer(false);

        QHostAddress ip = QHostAddress(ui->lineEdit_ip->text().split(":")[0]);
        int port = ui->lineEdit_ip->text().split(":")[1].toInt();
        client->setPort(port);
        client->setAddr(ip);
        client->connectToServer();

        gameWidget->setSocket(client);
    }
}

void menu::onConnected() {
    startGame();
}
