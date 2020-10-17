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
            area[accessArr2D(x, y)]->clear();
        }
    }
}

void Field::print() {
    for (int x = 0; x < maxArea; ++x) {
        for (int y = 0; y < maxArea; ++y) {
            area[accessArr2D(x, y)]->display();
        }
        std::cout << std::endl;
    }
}

bool Field::checkWin(int x, int y, symbol currPlayer) {
    int winCount = 0;
    int ix = 0;
    int iy = 0;
    bool winner = false;

    //horizontal
    for (ix = initI_negative(x); inArea(x, ix) && !winner; ix++) {
        if (area[accessArr2D(ix, y)]->state == currPlayer) {
            winCount++;
        } else {
            winCount = 0;
        }
        if (winCount >= win) {
            winner = currPlayer;
        }
    }

    //vertical
    for (iy = initI_negative(y); inArea(y, iy) && !winner; iy++) {
        if (area[accessArr2D(x, iy)]->state == currPlayer) {
            winCount++;
        } else {
            winCount = 0;
        }
        if (winCount >= win) {
            winner = currPlayer;
        }
    }

    //left up to right down
    for (ix = initI_negative(x), iy = initI_negative(y); inArea(x, ix) && inArea(y, iy) && !winner; ix++, iy++) {
        if (area[accessArr2D(ix, iy)]->state == currPlayer) {
            winCount++;
        } else {
            winCount = 0;
        }
        if (winCount >= win) {
            winner = currPlayer;
        }
    }

    //left down to right up
    for (ix = initI_negative(x), iy = initI_positive(y); inArea(x, ix) && inArea(y, iy) && !winner; ix++, iy--) {
        if (area[accessArr2D(ix, iy)]->state == currPlayer) {
            winCount++;
        } else {
            winCount = 0;
        }
        if (winCount >= win) {
            winner = currPlayer;
        }
    }

    return winner;
}


int Field::initI_negative(int z) {
    return (z - winDist < 0) ? 0 : z - winDist;
}

int Field::initI_positive(int z) {
    return (z + winDist >= maxArea) ? maxArea - 1 : z + winDist;
}

bool Field::inArea(int z, int iz) {
    return iz < ((z + winDist > maxArea) ? maxArea - 1 : z + winDist) && iz > ((z - winDist < 0) ? -1 : z - winDist);
}