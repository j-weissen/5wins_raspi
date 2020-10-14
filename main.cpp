#include "fivewins.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    fiveWins w;
    w.show();
    return a.exec();
}
