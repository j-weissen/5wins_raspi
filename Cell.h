//
// Created by maile on 07.10.2020.
//

#ifndef INC_5WINS_RASPI_CELL_H
#define INC_5WINS_RASPI_CELL_H

enum symbol{x,o,free};

class Cell {
public:
    Cell(int x, int y, symbol state) : x(x), y(y), state(state) {}
private:
    int x, y;
    symbol state;
    void clear();
    void set();
    void checkWin();
};


#endif //INC_5WINS_RASPI_CELL_H
