#include "field.h"

Field::Field(QGraphicsScene *scene) {
    this->scene = scene;
    init_Area();
}

Field::~Field()
{
    for (int y = 0; y < maxArea; ++y) {
        for (int x = 0; x < maxArea; ++x) {
            delete area[accessArr2D(x, y)];
        }
    }
}

void Field::init_Area() {
    for (int i = 0; i<15 ; ++i) {
        for (int j = 0; j<15 ; ++j) {
            area[i + j*15] = new CellGUI(i, j);
            scene->addItem(area[i + j*15]);
        }
    }
    scene->update();
}

void Field::clear() {
    for (int y = 0; y < maxArea; ++y) {
        for (int x = 0; x < maxArea; ++x) {
            delete area[accessArr2D(x, y)];
        }
    }
}

void Field::reset_Area()
{
    clear();
    init_Area();
}

int Field::accessArr2D(int x, int y) {
    return y * maxArea + x;
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

bool Field::checkWin(int x, int y, symbol currPlayerSymbol) {
    int winCount = 0;
    int ix = 0;
    int iy = 0;
    bool winner = false;

    //horizontal
    for (ix = initI_negative(x); inArea(ix) && !winner; ix++) {
        if (area[accessArr2D(ix, y)]->state == currPlayerSymbol) {
            winCount++;
        } else {
            winCount = 0;
        }
        if (winCount >= win) {
            winner = true;
        }
    }

    //vertical
    for (iy = initI_negative(y); inArea(iy) && !winner; iy++) {
        if (area[accessArr2D(x, iy)]->state == currPlayerSymbol) {
            winCount++;
        } else {
            winCount = 0;
        }
        if (winCount >= win) {
            winner = true;
        }
    }

    //left up to right down
    for (ix = initI_negative(x), iy = initI_negative(y); inArea(ix) && inArea(iy) && !winner; ix++, iy++) {
        if (area[accessArr2D(ix, iy)]->state == currPlayerSymbol) {
            winCount++;
        } else {
            winCount = 0;
        }
        if (winCount >= win) {
            winner = true;
        }
    }

    //left down to right up
    for (ix = initI_negative(x), iy = initI_positive(y); inArea(ix) && inArea(iy) && !winner; ix++, iy--) {
        if (area[accessArr2D(ix, iy)]->state == currPlayerSymbol) {
            winCount++;
        } else {
            winCount = 0;
        }
        if (winCount >= win) {
            winner = true;
        }
    }

    return winner;
}

