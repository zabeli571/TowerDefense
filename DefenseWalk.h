#ifndef TOWERDEFENSE_DEFENSEWALK_H
#define TOWERDEFENSE_DEFENSEWALK_H

#include <iostream>
#include <allegro5/allegro.h>
#include "MainObject.h"
#include "GameObject.h"
#include "Defense.h"

class DefenseWalk : public Defense
{

protected:
    void doAction(Play *play);
    void collisionWithOpponent(Opponent *opponent);
    void move();

public:
    static const int DEFENSE_WALK_CODE = 999;

    DefenseWalk(GameField *gameField);// przy konstruktorach defense, opponent, obstacle daje w argumentach wskaznik na gamefield by znac pole w ktorym chce narysowac
    DefenseWalk(GameField *gameField, ifstream *inputStream);
    DefenseWalk(GameField *gameField, ifstream *inputStream, bool exact);

    void displayOnConsole();
    ~DefenseWalk();
};

#endif //TOWERDEFENSE_DEFENSEWALK_H
