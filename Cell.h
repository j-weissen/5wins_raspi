#ifndef CELL_H
#define CELL_H


#include "iostream"

enum symbol{SYMBOL_X,SYMBOL_O,SYMBOL_FREE};

class Cell {
public:
    explicit Cell(symbol state);

    symbol state;

    void display() const;
};


#endif // CELL_H
