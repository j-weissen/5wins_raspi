#include "menu.h"
#include "ui_menu.h"
#include "QDir"
#include <QScreen>

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

    //PushButton CSS for Menu
    QString cssGreen = "QPushButton { background-color: rgb(89,201,38); border-style: double; border-width: 10px; border-radius: 10px; border-color: rgb(38,201,69); font: bold; min-width: 10em; } QPushButton:hover {border-color: rgb(38,131,69)}";
    ui->pushButton_local2Player->setStyleSheet(cssGreen);
    ui->pushButton_createServer->setStyleSheet(cssGreen);
    ui->pushButton_joinServer->setStyleSheet(cssGreen);
    ui->pushButton_exit->setStyleSheet("QPushButton { background-color: rgb(201,44,44); border-style: double; border-width: 10px; border-radius: 10px; border-color: rgb(180,44,44); font: bold; min-width: 10em; } QPushButton:hover {border-color: rgb(100,44,44)}");

    this->gameWidget = gameWidget;
    this->gameWidget->setMenu(this);
}

menu::~menu()
{
    delete ui;
}

void menu::on_pushButton_exit_clicked()
{
    qApp->quit();
}

void menu::on_pushButton_local2Player_clicked()
{
    if (gameWidget->getGame()->getTie() || gameWidget->getGame()->getWin()){
        gameWidget->resetGame();
    }
    gameWidget->showFullScreen();
    this->close();
}
