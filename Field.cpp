//
// Created by maile on 07.10.2020.
//

#include "Field.h"


int Field::accessArr2D(int x, int y) {
    return y * maxX + x;
}

void Field::clearAll() {
    for (int x = 0; x < maxX; ++x) {
        for (int y = 0; y < maxY; ++y) {
            area[accessArr2D(x, y)].clear();
        }
    }
}

void Field::print() {
    char c;

    for (int i = 0; i < maxX; ++i) {
        for (int j = 0; j < maxY; ++j) {
            //cell.display()
            if (area[accessArr2D(i, j)].state == f) {
                c = ' ';
            } else if (area[accessArr2D(i, j)].state == x) {
                c = 'x';
            } else {
                c = 'o';
            }

            std::cout << "[" << c << "]";
        }
        std::cout << std::endl;
    }
}

void Field::checkWin(int x, int y, symbol currPlayer) {
    int win = 0;
    int ix = 0;
    int iy = 0;

    //horizontal
    ix = (x-4 < 0) ? 0 : x-4;
    while (ix < ((x+4 > maxX) ? maxX - 1 : x+4) && win < 5) {
        if (area[accessArr2D(ix, y)].state == currPlayer) {
            win++;
        } else {
            win = 0;
        }
        ix++;
    }

    //vertical
    iy = (y-4 < 0) ? 0 : x-4;
    while (iy < ((y+4 > maxY) ? maxY - 1 : y+4) && win < 5) {
        if (area[accessArr2D(x, iy)].state == currPlayer) {
            win++;
        } else {
            win = 0;
        }
        iy++;
    }

    //left up to right down
    while (ix < ((x + 4 > maxX) ? maxX - 1 : x + 4) && iy < ((y+4 > maxY) ? maxY - 1 : y+4) && win < 5) {
        if (area[accessArr2D(ix, y)].state == currPlayer) {
            win++;
        } else {
            win = 0;
        }
        ix++;
        iy++;
    }
}