#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include "Fivewins.h"
#include "network/Network.h"
#include "network/NetworkTcpClient.h"
#include "network/NetworkTcpServer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class menu; }
QT_END_NAMESPACE

class menu : public QWidget
{
    Q_OBJECT

public:
    menu(fiveWins *gameWidget, QWidget *parent = nullptr);

    ~menu();

private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_local2Player_clicked();


    void on_pushButton_createServer_clicked();

    void on_pushButton_joinServer_clicked();

    void onConnected();

private:
    Ui::menu *ui;
    fiveWins *gameWidget;
    Network *socket;
    NetworkTcpServer *server;
    NetworkTcpClient *client;
    void startGame();

private slots:
    void resetMenu();
};
#endif // MENU_H
