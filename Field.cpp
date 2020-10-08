//
// Created by maile on 07.10.2020.
//

#include "Field.h"

int Field::accessArr2D(int x, int y) {
    return y*maxX+x;
}

void Field::clearAll() {

}

void Field::print() {
    char c;

    for (int i = 0; i < maxX; ++i) {
        for (int j = 0; j < maxY; ++j) {
            if (this->area[accessArr2D(i,j)].state == free)
        }
    }
}