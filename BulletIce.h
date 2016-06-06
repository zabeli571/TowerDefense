#ifndef TOWERDEFENSE_BULLETICE_H
#define TOWERDEFENSE_BULLETICE_H

#include <iostream>
#include <allegro5/allegro.h>
#include "MainObject.h"
#include "GameObject.h"
#include "Bullet.h"

class BulletIce : public Bullet
{
protected:
    void collisionWithOpponent(Opponent *opponent);
public:
    static const int BULLET_ICE_CODE = 2001;

    BulletIce(GameField *gameField, int x, int y);
    BulletIce(GameField *gameField, ifstream *inputStream, bool exact);

    ~BulletIce();
};


#endif //TOWERDEFENSE_BULLETICE_H
