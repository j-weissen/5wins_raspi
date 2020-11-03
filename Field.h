//
// Created by maile on 07.10.2020.
//

#ifndef INC_5WINS_RASPI_FIELD_H
#define INC_5WINS_RASPI_FIELD_H

#include <iostream>
#include "Cell.h"

class Field {


public:
    static const int maxArea = 15;
    Cell *area[maxArea * maxArea];

    void debugArea();

    static int accessArr2D(int x, int y);

    static bool inArea(int iz);

    bool checkWin(int x, int y, symbol currPlayer);

    void print();

    void init_Area();

private:
    static const int win = 5;
    static const int winDist = win - 1;

    void clearAll();


    static int initI_negative(int z);
    static int initI_positive(int z);
};

#endif //INC_5WINS_RASPI_FIELD_H