#ifndef TOWERDEFENSE_BULLET_H
#define TOWERDEFENSE_BULLET_H

#include "MainObject.h"
#include "GameObject.h"

class Bullet: public GameObject
{
private:
    static const int BULLET_CODE = 200;

    bool alreadyPunched;

    void move();
    void collisionWith(GameObject *anotherObject);
    void collisionWithOpponent(Opponent *opponent);
    void collisionWithObstacle(Obstacle *obstacle);
    void collisionWithDefense(Defense *defense);
    void collisionWithBullet(Bullet *bullet);
    void doAction(Play *play);

public:
    Bullet(GameField *gameField, int row, int column);
    ~Bullet();
};

#endif //TOWERDEFENSE_BULLET_H
