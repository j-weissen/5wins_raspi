#ifndef FIVEWINS_H
#define FIVEWINS_H

#include <QWidget>
#include <QGraphicsScene>
#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class fiveWins; }
QT_END_NAMESPACE

class fiveWins : public QWidget
{
    Q_OBJECT

public:
    fiveWins(QWidget *parent = nullptr);
    Game* getGame();

    void setupGui();

    void resetGame();
    void setMenu(QWidget *m);
    ~fiveWins();

public slots:
    bool eventFilter(QObject* watched, QEvent* event) override;


private slots:
    void on_pushButton_reset_clicked();

    void on_pushButton_exit_menu_clicked();

private:
    int playedGames;
    Ui::fiveWins *ui;
    QGraphicsScene *scene;
    QGraphicsTextItem *io;
    Game *game;
    QWidget *m;
    int sceneOffsetX, sceneOffsetY;
};
#endif // FIVEWINS_H
