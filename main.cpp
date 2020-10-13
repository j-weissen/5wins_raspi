#include <iostream>
#include "Game.h"

using namespace std;

int main() {

    Game game;
    Field field;

    cout << "Welcher Spieler beginnt? \n >> " << endl;
    cin >> game.currPlayer;

    // das wäre dann game.turn();


    return 0;
}