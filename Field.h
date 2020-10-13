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
    Cell area[maxX*maxY];

private:
    void clearAll();
    int accessArr2D(int x, int y);
    void print();
    void checkWin(int x, int y);
};


#endif //INC_5WINS_RASPI_FIELD_H
