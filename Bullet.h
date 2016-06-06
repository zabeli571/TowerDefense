#ifndef TOWERDEFENSE_BULLET_H
#define TOWERDEFENSE_BULLET_H

#include "MainObject.h"
#include "GameObject.h"

class Bullet: public GameObject
{
protected:

    bool alreadyPunched;

    void move();
    void collisionWith(GameObject *anotherObject);
    void collisionWithOpponent(Opponent *opponent);
    void collisionWithObstacle(Obstacle *obstacle);
    void collisionWithDefense(Defense *defense);
    void collisionWithBullet(Bullet *bullet);
    void doAction(Play *play);

public:
    static const int BULLET_CODE = 200;

    Bullet(GameField *gameField, int x, int y);
    Bullet(GameField *gameField, ifstream *inputStream, bool exact);

    void saveToStreamExact(ofstream* outputStream);

    ~Bullet();
};

#endif //TOWERDEFENSE_BULLET_H
