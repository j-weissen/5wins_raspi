//
// Created by maile on 07.10.2020.
//

#ifndef INC_5WINS_RASPI_FIELD_H
#define INC_5WINS_RASPI_FIELD_H

#include <iostream>
#include "Cell.h"

class Field {

public:
    static const int maxArea = 5;
    Cell *area[maxArea * maxArea];

    Field();
    void init_Area();
    void clear();

    static int accessArr2D(int x, int y);

    static bool inArea(int iz);

    bool checkWin(int x, int y, symbol currPlayerSymbol);
    int checkCon(int x, int y, symbol currPlayerSymbol, symbol enemy);

    bool isSurrounded(int x, int y, int range);
    static bool checkRange(int start, int pos, int range);

    bool checkTie();

    void print();

private:
    static const int win = 5;
    static const int winDist = win - 1;


    static int initI_negative(int z, int range = winDist);
    static int initI_positive(int z, int range = winDist);
};

#endif //INC_5WINS_RASPI_FIELD_H