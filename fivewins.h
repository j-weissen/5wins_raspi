#ifndef FIVEWINS_H
#define FIVEWINS_H

#include <QWidget>
#include <QGraphicsScene>
#include "game.h"
#include "network/Network.h"
#include "network/dataRecievedEvent.h"

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
    void endGame();
    void setMenu(QWidget *m);
    void initGame();

    Network *getSocket();
    void setSocket(Network *socket);

    void setIsServer(bool isServer);
    void resetActionOrigin();

    ~fiveWins();

public slots:
    bool eventFilter(QObject* watched, QEvent* event) override;


private slots:
    void on_pushButton_reset_clicked();

    void on_pushButton_exit_menu_clicked();

    void onDataRecieved();

    void on_pushButton_undo_clicked();

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
    QString encodeTurn(int x, int y);
    QString encodeAction(int action);
    DataRecievedEvent* decodeDataToEvent(QString data);
    void exit();
    void reset();
    void undo();
    bool sendUpdates();

signals:
    void resetSockets();
};
#endif // FIVEWINS_H
