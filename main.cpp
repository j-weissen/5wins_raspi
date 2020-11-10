#include <iostream>
#include "Game.h"

using namespace std;

int main() {
    Game game(SYMBOL_X, TYPE_HUMAN, TYPE_HUMAN);
    bool win = false;

    game.field.print();

    while (!win) {
        game.turn(&win);
    }

    cout << "Player \"" << game.currPlayer->toChar() << "\" has won!" << endl;

    return 0;
}