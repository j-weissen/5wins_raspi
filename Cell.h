//
// Created by maile on 07.10.2020.
//

#ifndef INC_5WINS_RASPI_CELL_H
#define INC_5WINS_RASPI_CELL_H

#include <iostream>


enum symbol{SYMBOL_X,SYMBOL_O,SYMBOL_FREE};

class Cell {
public:
    explicit Cell(symbol state);

    symbol state;

    void display() const;
};

#endif //INC_5WINS_RASPI_CELL_H