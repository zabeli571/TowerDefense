#ifndef TOWERDEFENSE_OPPONENTFLY_H
#define TOWERDEFENSE_OPPONENTFLY_H

#include <iostream>
#include <allegro5/allegro.h>
#include "MainObject.h"
#include "GameObject.h"
#include "Opponent.h"

class OpponentFly : public Opponent
{
protected:
    void move();
public:
    static const int OPPONENT_FLY_CODE = 102;


    OpponentFly(GameField *gameField);
    OpponentFly(GameField *gameField,  int row, int column);
    OpponentFly(GameField *gameField, ifstream *inputStream);

    void displayOnConsole();
    ~OpponentFly();
};


#endif //TOWERDEFENSE_OPPONENTFLY_H
