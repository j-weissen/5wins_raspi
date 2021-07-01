#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include "fivewins.h"

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


private:
    Ui::menu *ui;
    fiveWins *gameWidget;
};
#endif // MENU_H
