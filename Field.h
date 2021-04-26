#ifndef FIELD_H
#define FIELD_H

#include "cell_gui.h"
#include <QGraphicsScene>

class Field {


public:
    static const int maxArea = 15;
    CellGUI *area[maxArea * maxArea];
    QGraphicsScene *scene;

    Field(QGraphicsScene *scene);
    ~Field();
    void init_Area();
    void clear();
    void reset_Area();

    static int accessArr2D(int x, int y);

    static bool inArea(int iz);

    bool checkWin(int x, int y, symbol currPlayerSymbol);
    bool checkTie();
    void print();


private:
    static const int win = 5;
    static const int winDist = win - 1;

    static int initI_negative(int z, int range=winDist);
    static int initI_positive(int z, int range=winDist);
};

#endif // FIELD_H
