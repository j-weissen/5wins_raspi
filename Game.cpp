//
// Created by maile on 07.10.2020.
//

#include "Game.h"
#include <iostream>
#include <pthread.h>

Game::Game(symbol startPlayer, playerType typePlayerX, playerType typePlayerO){
    Field();
    playerX = new Player(SYMBOL_X, typePlayerX);
    playerO = new Player(SYMBOL_O, typePlayerO);
    currPlayer = (startPlayer == SYMBOL_X) ? playerX : playerO;
}

Game::~Game(){
    delete playerX;
    delete playerO;

}

void Game::switchCurrPlayer(){
    currPlayer = (currPlayer == playerX) ? playerO : playerX;
}

void Game::turn(bool *win, bool *tie){


    (currPlayer->type == TYPE_HUMAN) ? inputHuman() : inputAI();

    field.area[Field::accessArr2D(xIn, yIn)]->state = currPlayer->playerSymbol;
    *win = field.checkWin(xIn, yIn, currPlayer->playerSymbol);
    *tie = field.checkTie();


    field.print();

    if(!*win){
        switchCurrPlayer();
    }
}

void Game::inputHuman(){
    bool isFree = true;

    do{
        if(!isFree){
            std::cout << "Choose an empty field!" << std::endl;
        }
        std::cout << "Spieler " << currPlayer->toChar() << ", Row: " << std::endl;
        std::cin >> yIn;
        std::cout << "Spieler " << currPlayer->toChar() << ", Collumn: " << std::endl;
        std::cin >> xIn;
        if(Field::inArea(xIn) && Field::inArea(yIn)){
            isFree = field.area[Field::accessArr2D(xIn, yIn)]->state == SYMBOL_FREE;
        } else{
            isFree = false;
        }
    } while(!isFree);
}

void Game::inputAI(){
    int bestScore = INT32_MIN;
    int score;

    aiTestField = field;

    for(int x = 0; x < Field::maxArea; x++){
        for(int y = 0; y < Field::maxArea; y++){
            if(aiTestField.area[Field::accessArr2D(x, y)]->state == SYMBOL_FREE && aiTestField.isSurrounded(x, y, 2)){
                aiTestField.isSurrounded(x, y, 2);
                score = aiMinimax(1, true, currPlayer->playerSymbol, x, y);
                if(score > bestScore){
                    bestScore = score;
                    aiBestMove[0] = x;
                    aiBestMove[1] = y;
                }
            }
        }
    }
    xIn = aiBestMove[0];
    yIn = aiBestMove[1];
    aiBestMove[0] = NULL;
    aiBestMove[1] = NULL;
}

int Game::aiMinimax(int depth, bool isMaximizing, symbol identity, int tempX, int tempY){
    int rv;
    symbol enemy = (identity == SYMBOL_X) ? SYMBOL_O : SYMBOL_X;
    int aiScore;
    int humanScore;

    if(depth > 4){
        return bestScore(depth, identity, enemy, tempX, tempY);
    }

    rv = bestScore(depth, identity, enemy, tempX, tempY);

    if(isMaximizing){
        for(int x = 0; x < Field::maxArea; x++){
            for(int y = 0; y < Field::maxArea; y++){
                aiCheckMove(depth, tempX, tempY, identity, enemy, &aiScore, rv, isMaximizing);
            }
        }
        aiTestField.area[Field::accessArr2D(aiBestMove[0], aiBestMove[1])]->state = identity;
    } else{
        for(int x = 0; x < Field::maxArea; x++){
            for(int y = 0; y < Field::maxArea; y++){
                aiCheckMove(depth, tempX, tempY, enemy, identity, &humanScore, rv, isMaximizing);
            }
        }
        aiTestField.area[Field::accessArr2D(aiBestMove[0], aiBestMove[1])]->state = enemy;
    }
    aiTestField.print();
    return rv;
}

int Game::bestScore(int depth, symbol identity, symbol enemy, int x, int y){
    int rv;
    if(field.checkWin(x, y, identity)){
        rv = 1000 / depth;
    } else if(field.checkWin(x, y, enemy)){
        rv = -1000 / depth;
    } else if(field.checkTie()){
        rv = 0;
    } else{
        rv = 1 + aiTestField.checkCon(x, y, identity, enemy) / depth;
    }
    return rv;
}

void Game::aiCheckMove(int depth, int x, int y, symbol identity, symbol enemy, int *currScore, int prev, bool isMaximizing){
    bool aiTurn = (identity == currPlayer->playerSymbol);

    if(aiTestField.area[Field::accessArr2D(x, y)]->state == SYMBOL_FREE &&
            aiTestField.isSurrounded(x, y, 2)){
        aiTestField.area[Field::accessArr2D(x, y)]->state = identity;
        *currScore = prev + aiMinimax(depth + 1, !isMaximizing, enemy, x, y) + bestScore(depth, identity, enemy, x, y);
        aiTestField.area[Field::accessArr2D(x, y)]->state = SYMBOL_FREE;
        if(aiTurn && *currScore > aiBestScore){
            aiBestScore = *currScore;
            aiBestMove[0] = x;
            aiBestMove[1] = y;
        }else if (!aiTurn && *currScore > humanBestScore){
            humanBestScore = *currScore;
            humanBestMove[0] = x;
            humanBestMove[1] = y;
        }
    }
}