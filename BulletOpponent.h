#ifndef TOWERDEFENSE_BULLETOPPONENT_H
#define TOWERDEFENSE_BULLETOPPONENT_H

#include <iostream>
#include <allegro5/allegro.h>
#include "MainObject.h"
#include "GameObject.h"
#include "Bullet.h"

class BulletOpponent : public Bullet
{
protected:
    static const int BULLET_OPPONENT_CODE = 20011;

    void move();
    void collisionWithOpponent(Opponent *opponent);
    void collisionWithObstacle(Obstacle *obstacle);
    void collisionWithDefense(Defense *defense);
    void attackObject(GameObject *gameObject);

public:
    BulletOpponent(GameField *gameField, int x, int y);
    ~BulletOpponent();

};

#endif //TOWERDEFENSE_BULLETOPPONENT_H
