#include <iostream>
#include "Game.h"

using namespace std;

int main() {
    Game game(SYMBOL_X, TYPE_HUMAN, TYPE_HUMAN);
    bool win = false;
    bool tie = false;

    game.field.print();

    while (!win && !tie) {
        game.turn(&win, &tie);
    }

    if (win) {
        cout << "Player \"" << game.currPlayer->toChar() << "\" has won!" << endl;
    } else {
        cout << "It's a tie!" << endl;
    }

    return 0;
}