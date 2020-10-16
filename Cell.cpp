//
// Created by maile on 07.10.2020.
//

#include "Cell.h"

void Cell::clear() {
    state = f;
}

void Cell::display() {
    char c;
    if (state == f) {
        c = ' ';
    } else if (state == x) {
        c = 'x';
    } else {
        c = 'o';
    }

    std::cout << "[" << c << "]";
}
