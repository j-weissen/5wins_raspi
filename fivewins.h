#ifndef FIVEWINS_H
#define FIVEWINS_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class fiveWins; }
QT_END_NAMESPACE

class fiveWins : public QWidget
{
    Q_OBJECT

public:
    fiveWins(QWidget *parent = nullptr);
    ~fiveWins();

private:
    Ui::fiveWins *ui;
};
#endif // FIVEWINS_H
