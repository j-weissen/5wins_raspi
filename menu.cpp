#include "menu.h"
#include "ui_menu.h"
#include "QDir"


menu::menu(fiveWins *gameWidget, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::menu)
{
    ui->setupUi(this);
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    qDebug() << QCoreApplication::applicationDirPath();
    QPixmap mop("5wins-logo.png");
    ui->label_logo->setPixmap(mop);
    ui->label_logo->setScaledContents(true);

    ui->pushButton_local2Player->setStyleSheet("QPushButton { background-color: rgb(89,201,38); border-style: double; border-width: 10px; border-radius: 10px; border-color: rgb(38,201,69); font: bold 18px; min-width: 10em; } QPushButton:hover {border-color: rgb(38,131,69)}");
    ui->pushButton_createServer->setStyleSheet("QPushButton { background-color: rgb(89,201,38); border-style: double; border-width: 10px; border-radius: 10px; border-color: rgb(38,201,69); font: bold 18px; min-width: 10em; } QPushButton:hover {border-color: rgb(38,131,69)}");
    ui->pushButton_joinServer->setStyleSheet("QPushButton { background-color: rgb(89,201,38); border-style: double; border-width: 10px; border-radius: 10px; border-color: rgb(38,201,69); font: bold 18px; min-width: 10em; } QPushButton:hover {border-color: rgb(38,131,69)}");
    ui->pushButton_vsAI->setStyleSheet("QPushButton { background-color: rgb(89,201,38); border-style: double; border-width: 10px; border-radius: 10px; border-color: rgb(38,201,69); font: bold 18px; min-width: 10em; } QPushButton:hover {border-color: rgb(38,131,69)}");
    ui->pushButton_exit->setStyleSheet("QPushButton { background-color: rgb(201,44,44); border-style: double; border-width: 10px; border-radius: 10px; border-color: rgb(180,44,44); font: bold 18px; min-width: 10em; } QPushButton:hover {border-color: rgb(100,44,44)}");

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
    gameWidget->show();
    this->close();
}

