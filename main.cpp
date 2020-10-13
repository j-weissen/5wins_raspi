#include <iostream>
#include "Game.h"

using namespace std;

int main() {

    Game game;
    Field field;

    cout << "Welcher Spieler beginnt? \n >> " << endl;
    cin >> game.currPlayer;

    // das wäre dann game.turn();
    int x, y;

    // Input
    cout << "Spieler " << currPlayer << ", Row: " << endl;
    cin >> y;
    cout << "Spieler " << currPlayer << ", Collumn: " << endl;
    cin >> x;

    field.area[Field::accessArr2D(x, y)].set(x, y);

    return 0;
}