//
// Created by maile on 07.10.2020.
//

#include "Cell.h"

void Cell::clear() {
    state = SYMBOL_FREE;
}

void Cell::display() {
    char c;
    if (state == SYMBOL_FREE) {
        c = ' ';
    } else if (state == SYMBOL_X) {
        c = 'x';
    } else {
        c = 'o';
    }

    std::cout << "[ " << c << " ]";
}

Cell::Cell(symbol state) : state(state) {}
