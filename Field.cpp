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
    std::cout << "\t";
    for (int i = 0; i < maxArea; ++i) {
        std::cout << ((i < 10) ? "  " + std::to_string(i) + "  " : " " + (std::to_string(i / 10) + " " +
                                                                          std::to_string(i % 10) + " "));
    }
    std::cout << std::endl;
    for (int y = 0; y < maxArea; ++y) {
        std::cout << std::to_string(y) + "\t";
        for (int x = 0; x < maxArea; ++x) {
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
    for (ix = initI_negative(x); inArea(ix) && !winner; ix++) {
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
    for (iy = initI_negative(y); inArea(iy) && !winner; iy++) {
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
    for (ix = initI_negative(x), iy = initI_negative(y); inArea(ix) && inArea(iy) && !winner; ix++, iy++) {
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
    for (ix = initI_negative(x), iy = initI_positive(y); inArea(ix) && inArea(iy) && !winner; ix++, iy--) {
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

bool Field::inArea(int iz) {
    return iz < maxArea && iz >= 0;
}

void Field::init_Area() {
    for (int y = 0; y < maxArea; ++y) {
        for (int x = 0; x < maxArea; ++x) {
            area[accessArr2D(x, y)] = new Cell(SYMBOL_FREE);
        }
    }
}

void Field::debugArea() {
    area[accessArr2D(0, 0)]->state = SYMBOL_O;
    area[accessArr2D(0, 1)]->state = SYMBOL_O;
    area[accessArr2D(0, 3)]->state = SYMBOL_O;
    area[accessArr2D(0, 4)]->state = SYMBOL_O;
}
