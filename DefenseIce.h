#ifndef TOWERDEFENSE_DEFENCEICE_H
#define TOWERDEFENSE_DEFENCEICE_H

#include <iostream>
#include <allegro5/allegro.h>
#include "MainObject.h"
#include "GameObject.h"
#include "Defense.h"

class DefenseIce : public Defense
{

protected:
    void doAction(Play *play);
    static const int ATTACK_INTERVAL = 4000;

public:
    static const int DEFENSE_ICE_CODE = 99;

    DefenseIce(GameField *gameField);// przy konstruktorach defense, opponent, obstacle daje w argumentach wskaznik na gamefield by znac pole w ktorym chce narysowac
    DefenseIce(GameField *gameField, ifstream *inputStream);
    DefenseIce(GameField *gameField, ifstream *inputStream, bool exact);

    void displayOnConsole();
    ~DefenseIce();
};


#endif //TOWERDEFENSE_DEFENCEICE_H
