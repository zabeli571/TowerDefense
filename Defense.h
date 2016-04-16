#ifndef DEFENSE_H
#define DEFENSE_H

#include <iostream>
#include <allegro5/allegro.h>
#include "MainObject.h"
#include "GameObject.h"

using namespace std;

class Defense: public GameObject
{
private:
    int hp;
public:
    static const int DEFENSE_CODE = 9;
    Defense(GameField *gameField, int hp);// przy konstruktorach defense, opponent, obstacle daje w argumentach wskaznik na gamefield by znac pole w ktorym chce narysowac
    void displayOnConsole();
    ~Defense();
};

#endif