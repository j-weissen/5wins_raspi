#include "field.h"
#include <iostream>

Field::Field(QGraphicsScene *scene) {
    this->scene = scene;
    previouslyChanged = nullptr;
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
    for (int i = 0; i<maxArea ; ++i) {
        for (int j = 0; j<maxArea ; ++j) {
            area[i + j*maxArea] = new CellGUI(i, j);
            scene->addItem(area[i + j*maxArea]);
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

CellGUI* Field::accessCell(int x, int y){
    return area[accessArr2D(x, y)];
}

void Field::reset_Area()
{
    clear();
    init_Area();
}

int Field::accessArr2D(int x, int y)
{
    return y * maxArea + x;

}

bool Field::inArea(int x, int y) {
    return (x < maxArea) && (x >= 0) && (y < maxArea) && (y >= 0);
}

bool Field::checkWin() {
    if (previouslyChanged != nullptr) {
        int winCount = 0;
        symbol playerID = previouslyChanged->state;
        int x = previouslyChanged->getX();
        int y = previouslyChanged->getY();
        int ix;
        int iy;
        int maxDist;
        bool isWin = false;

        //horizontal
        for (ix = initI_negative(x); inArea(ix, y) && !isWin; ix++) {
            if (accessCell(ix, y)->state == playerID) {
                winCount++;
            } else {
                winCount = 0;
            }
            if (winCount >= win) {
                isWin = true;
            }
        }

        //vertical
        winCount = 0;
        for (iy = initI_negative(y); inArea(x, iy) && !isWin; iy++) {
            if (accessCell(x, iy)->state == playerID) {
                winCount++;
            } else {
                winCount = 0;
            }
            if (winCount >= win) {
                isWin = true;
            }
        }

        //left down to right up
        winCount = 0;
        maxDist = getMaxDiagonalDistLeftDown(x, y);
        for (ix = initI_negative(x, maxDist), iy = initI_negative(y, maxDist); inArea(ix, iy) && !isWin; ix++, iy++) {
            if (accessCell(ix, iy)->state == playerID) {
                winCount++;
            } else {
                winCount = 0;
            }
            if (winCount >= win) {
                isWin = true;
            }
        }

        //left up to right down
        winCount = 0;
        maxDist = getMaxDiagonalDistLeftUp(x, y);
        for (ix = initI_negative(x, maxDist), iy = initI_positive(y, maxDist); inArea(ix, iy) && !isWin; ix++, iy--) {
            if (accessCell(ix, iy)->state == playerID) {
                winCount++;
            } else {
                winCount = 0;
            }
            if (winCount >= win) {
                isWin = true;
            }
        }

        return isWin;
    }
    return false;
}

/**
     * @param z Wert
     * @return Minimalwert zum Ende des Feldes, bzw. zur winDist=4
     */
int Field::initI_negative(int z) {
    return std::max(z - winDist, 0);
}

/**
     * @param z    Wert
     * @param dist Maximale Distanz zum Subtrahieren
     * @return Maximalwert zum Ende des Feldes, bzw. zur dist
     */
int Field::initI_negative(int z, int dist) {
    return std::max(z - dist, 0);
}

/**
     * @param z    Wert
     * @param dist Maximale Distanz zum Addieren
     * @return Maximalwert zum Ende des Feldes, bzw. zur dist
     */
int Field::initI_positive(int z, int dist) {
    return (z + dist >= maxArea) ? maxArea - 1 : z + dist;
}

/**
     * @param x Spalte
     * @param y Reihe
     * @return die maximale diagonale Distanz zum initialisieren ins negative nach links oben
     */
int Field::getMaxDiagonalDistLeftUp(int x, int y) {
    int rv = -1;
    int dist;
    bool success;

    for (dist = 1, success = true; dist <= winDist && success; dist++) {
        success = inArea(x - dist, y + dist);
        if (!success) {
            rv = dist - 1;
        }
    }

    rv = (rv == -1) ? winDist : rv;

    return rv;
}

/**
     * @param x Spalte
     * @param y Reihe
     * @return die maximale diagonale Distanz zum initialisieren ins negative nach links unten
     */
int Field::getMaxDiagonalDistLeftDown(int x, int y) {
    int rv = -1;
    int dist;
    bool success;

    for (dist = 1, success = true; dist <= winDist && success; dist++) {
        success = inArea(x - dist, y - dist);
        if (!success) {
            rv = dist - 1;
        }
    }

    rv = (rv == -1) ? winDist : rv;

    return rv;
}

bool Field::checkTie() {
    bool rv = true;
    int x = 0;
    int y;

    while (x < maxArea && rv) {
        y = 0;
        while (y < maxArea && rv) {
            rv = (area[accessArr2D(x,y)]->state != SYMBOL_FREE);
            y++;
        }
        x++;
    }
    return rv;
}

void Field::setPrevCell(CellGUI *cell)
{
    previouslyChanged = cell;
}

bool Field::undo(){
    if (previouslyChanged != nullptr && previouslyChanged->state != SYMBOL_FREE){
        previouslyChanged->state = SYMBOL_FREE;
        previouslyChanged->update();
        return true;
    }
    return false;
}
