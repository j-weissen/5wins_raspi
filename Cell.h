//
// Created by maile on 07.10.2020.
//

#ifndef INC_5WINS_RASPI_CELL_H
#define INC_5WINS_RASPI_CELL_H

enum symbol{x,o,f};

class Cell {
public:
    Cell(symbol state) : state(state){}
    symbol state;
    void clear();
    void set(int x, int y);
};

#endif //INC_5WINS_RASPI_CELL_H