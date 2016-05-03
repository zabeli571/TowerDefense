#ifndef TOWERDEFENSE_BULLET_H
#define TOWERDEFENSE_BULLET_H

#include "MainObject.h"
#include "GameObject.h"

class Bullet: public GameObject
{
public:

    Bullet(GameField *gameField, int row, int column);
};


#endif //TOWERDEFENSE_BULLET_H
