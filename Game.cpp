//
// Created by maile on 07.10.2020.
//

#include "Game.h"
#include <iostream>

Game::Game(symbol startPlayer, playerType typePlayerX, playerType typePlayerO) {
    Field();
    playerX = new Player(SYMBOL_X, typePlayerX);
    playerO = new Player(SYMBOL_O, typePlayerO);
    currPlayer = (startPlayer == SYMBOL_X) ? playerX : playerO;
}

Game::~Game() {
    delete playerX;
    delete playerO;

}

void Game::switchCurrPlayer() {
    currPlayer = (currPlayer == playerX) ? playerO : playerX;
}

void Game::turn(bool *win, bool *tie) {


    (currPlayer->type == TYPE_HUMAN) ? inputHuman() : inputAI();

    field.area[Field::accessArr2D(xIn, yIn)]->state = currPlayer->playerSymbol;

    *win = field.checkWin(xIn, yIn, currPlayer->playerSymbol);
    *tie = field.checkTie();



    field.print();

    if (!*win) {
        switchCurrPlayer();
    }
}

void Game::inputHuman() {
    bool isFree = true;

    do {
        if (!isFree) {
            std::cout << "Choose an empty field!" << std::endl;
        }
        std::cout << "Spieler " << currPlayer->toChar() << ", Row: " << std::endl;
        std::cin >> yIn;
        std::cout << "Spieler " << currPlayer->toChar() << ", Collumn: " << std::endl;
        std::cin >> xIn;
        if (Field::inArea(xIn) && Field::inArea(yIn)) {
            isFree = field.area[Field::accessArr2D(xIn, yIn)]->state == SYMBOL_FREE;
        } else {
            isFree = false;
        }
    } while (!isFree);
}

void Game::inputAI() {
    int bestScore = INT32_MIN;
    int score;

    aiTestField = field;

    for(int x = 0; x < Field::maxArea; x++){
        for(int y = 0; y < Field::maxArea; y++){
            if(aiTestField.area[Field::accessArr2D(x, y)]->state == SYMBOL_FREE){
                score = aiMinimax(0, true, currPlayer->playerSymbol, x, y);
                if(score > bestScore){
                    bestScore = score;
                    xIn = x;
                    yIn = y;
                }
            }
        }
    }
}

int Game::aiMinimax(int depth, bool isMaximizing, symbol identity, int tempX, int  tempY){
    if(depth > 2){
        return NULL;
    }

    int rv;
    bool rtnBool;
    symbol enemy = (identity == SYMBOL_X) ? SYMBOL_O : SYMBOL_X;
    int aiScore;
    int humanScore;

    if(field.checkWin(tempX, tempY, identity)){
        rv = 1;
    } else if(field.checkWin(tempX, tempY, enemy)){
        rv = -1;
    } else if(field.checkTie()){
        rv = 0;
    }

    if(isMaximizing){
        for(int x = 0; x < Field::maxArea; x++){
            for(int y = 0; y < Field::maxArea; y++){
                if(aiTestField.area[Field::accessArr2D(x, y)]->state == SYMBOL_FREE){
                    aiTestField.area[Field::accessArr2D(x, y)]->state = identity;
                    aiScore = rv + aiMinimax(depth + 1, false, enemy, x, y);
                    aiTestField.area[Field::accessArr2D(x, y)]->state = SYMBOL_FREE;
                    aiBestScore = std::max(aiScore, aiBestScore);
                }
            }
        }
        return aiBestScore;
    }else{
        for(int x = 0; x < Field::maxArea; x++){
            for(int y = 0; y < Field::maxArea; y++){
                if(aiTestField.area[Field::accessArr2D(x, y)]->state == SYMBOL_FREE){
                    aiTestField.area[Field::accessArr2D(x, y)]->state = enemy;
                    humanScore = rv + aiMinimax(depth + 1, true, identity, x, y);
                    aiTestField.area[Field::accessArr2D(x, y)]->state = SYMBOL_FREE;
                    humanBestScore = std::min(humanScore, humanBestScore);
                }
            }
        }
        return humanBestScore;
    }
}