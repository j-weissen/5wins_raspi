//
// Created by maile on 07.10.2020.
//

#ifndef INC_5WINS_RASPI_CELL_H
#define INC_5WINS_RASPI_CELL_H

enum symbol{x,o,f};

class Cell {
public:
    Cell(int x, int y, symbol state) : x(x), y(y), state(state){}
    symbol state;
    int x, y;
    void clear();
    void set();
    void checkWin();
    //checkwin() und x,y in Field?
private:

};


#endif //INC_5WINS_RASPI_CELL_H
