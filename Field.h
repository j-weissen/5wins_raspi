//
// Created by maile on 07.10.2020.
//

#ifndef INC_5WINS_RASPI_FIELD_H
#define INC_5WINS_RASPI_FIELD_H

#include <iostream>
#include "Cell.h"

class Field {
    static const int maxArea = 15;

public:
    Cell area[maxArea * maxArea];
    static int accessArr2D(int x, int y);

private:
    static const int win = 5;
    static const int winDist = win-1;
    void clearAll();
    void print();
    symbol checkWin(int x, int y, symbol currPlayer);
    int initI_negative(int z);
    int initI_positive(int z);
    bool inArea(int z, int iz);
};

#endif //INC_5WINS_RASPI_FIELD_H