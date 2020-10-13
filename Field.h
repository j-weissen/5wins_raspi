//
// Created by maile on 07.10.2020.
//

#ifndef INC_5WINS_RASPI_FIELD_H
#define INC_5WINS_RASPI_FIELD_H

#include <iostream>
#include "Cell.h"

class Field {
    static const int maxX = 15;
    static const int maxY = 15;

public:
    Cell area[maxX * maxY];
    Field();
    static int accessArr2D(int x, int y);

private:
    void clearAll();
    void print();
    void checkWin();
};

#endif //INC_5WINS_RASPI_FIELD_H