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
    ~fiveWins();

public slots:
    bool eventFilter(QObject* watched, QEvent* event) override;


private slots:
    void on_pushButton_reset_clicked();

private:
    int playedGames;
    Ui::fiveWins *ui;
    QGraphicsScene *scene;
    QGraphicsTextItem *io;
    Game *game;
    static constexpr int SCENE_OFFSET= 100;

    void resetGame();

};
#endif // FIVEWINS_H
