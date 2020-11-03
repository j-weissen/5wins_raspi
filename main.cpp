#include <iostream>
#include "Game.h"

using namespace std;

int main() {
    Game game(x); //o wird anfangen wegen dem switchplayer am Anfang des turn loops
    bool win = false;
    game.field.debugArea();

    game.field.print();

    while (!win) {
        game.turn(&win);
    }


    cout << "Player \"" << ((game.currPlayer == x) ? "X" : "O") << "\" has won!" << endl;

    return 0;
}