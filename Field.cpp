//
// Created by maile on 07.10.2020.
//

#include "Field.h"


int Field::accessArr2D(int x, int y) {
    return y * maxArea + x;
}

void Field::clearAll() {
    for (int x = 0; x < maxArea; ++x) {
        for (int y = 0; y < maxArea; ++y) {
            area[accessArr2D(x, y)].clear();
        }
    }
}

void Field::print() {
    for (int x = 0; x < maxArea; ++x) {
        for (int y = 0; y < maxArea; ++y) {
            area[accessArr2D(x, y)].display();
        }
        std::cout << std::endl;
    }
}

symbol Field::checkWin(int x, int y, symbol currPlayer) {
    int winCount = 0;
    int ix = 0;
    int iy = 0;
    symbol winner = f;

    //horizontal
    ix = initI_negative(x);
    while (inArea(x, ix) && winner == f) {
        if (area[accessArr2D(ix, y)].state == currPlayer) {
            winCount++;
        } else {
            winCount = 0;
        }
        if (winCount >= win) {
            winner = currPlayer;
        }

        ix++;
    }

    //vertical
    iy = initI_negative(y);
    while (inArea(y, iy) && winner == f) {
        if (area[accessArr2D(x, iy)].state == currPlayer) {
            winCount++;
        } else {
            winCount = 0;
        }
        if (winCount >= win) {
            winner = currPlayer;
        }

        iy++;
    }

    //left up to right down
    ix = initI_negative(x);
    iy = initI_negative(y);
    while (inArea(x, ix) && inArea(y, iy) && winner == f) {
        if (area[accessArr2D(ix, iy)].state == currPlayer) {
            winCount++;
        } else {
            winCount = 0;
        }
        if (winCount >= win) {
            winner = currPlayer;
        }

        ix++;
        iy++;
    }

    //left down to right up
    ix = initI_negative(x);
    iy = initI_positive(y);
    while (inArea(x, ix) && inArea(y, iy) && winCount < win) {
        if (area[accessArr2D(ix, iy)].state == currPlayer) {
            winCount++;
        } else {
            winCount = 0;
        }
        if (winCount >= win) {
            winner = currPlayer;
        }

        ix++;
        iy--;
    }

    return winner;
}


int Field::initI_negative(int z) {
    return (z-winDist < 0) ? 0 : z-winDist;
}

int Field::initI_positive(int z) {
    return (z+winDist >= maxArea) ? maxArea-1 : z+winDist;
}

bool Field::inArea(int z, int iz) {
    return iz < ((z+winDist > maxArea) ? maxArea-1 : z+winDist) && iz > ((z-winDist < 0) ? -1 : z-winDist);
}