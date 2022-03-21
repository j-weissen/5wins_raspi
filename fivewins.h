#ifndef FIVEWINS_H
#define FIVEWINS_H

#include <QWidget>
#include <QGraphicsScene>
#include "game.h"
#include "network/Network.h"

QT_BEGIN_NAMESPACE
namespace Ui { class fiveWins; }
QT_END_NAMESPACE

class fiveWins : public QWidget
{
    Q_OBJECT

public:
    QString static messageSeparator;
    QString static textSeparator;
    static constexpr int serverPort = 12345;
    static constexpr int clientPort = 12347;
    fiveWins(QWidget *parent = nullptr);
    Game* getGame();
    void setupGui();
    void resetGame();
    void setMenu(QWidget *m);
    void postMenuInit();

    Network *getSocket();
    void setSocket(Network *socket);

    void setIsServer(bool isServer);

    ~fiveWins();

public slots:
    bool eventFilter(QObject* watched, QEvent* event) override;


private slots:
    void on_pushButton_reset_clicked();

    void on_pushButton_exit_menu_clicked();

    void onDataRecieved();

private:
    int playedGames;
    Ui::fiveWins *ui;
    QGraphicsScene *scene;
    QGraphicsTextItem *io;
    Game *game;
    QWidget *m;
    int sceneOffsetX, sceneOffsetY;
    Network *socket;
    bool isServer;
};
#endif // FIVEWINS_H
