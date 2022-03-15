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

    static bool inArea(int x, int y);

    bool checkWin();
    bool checkTie();
    void print();

    void setPrevCell(CellGUI* cell);


private:
    static const int win = 5;
    static const int winDist = win;

    int initI_negative(int z);
    int initI_negative(int z, int dist);
    int initI_positive(int z, int dist);
    int getMaxDiagonalDistLeftUp(int x, int y);
    int getMaxDiagonalDistLeftDown(int x, int y);
    CellGUI *previouslyChanged;

    CellGUI* accessCell(int x, int y);
};

#endif // FIELD_H
