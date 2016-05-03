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
    static const int ATTACK_INTERVAL = 3000;
    chrono::milliseconds lastAttackTime;

    void move();
    void collisionWith(GameObject *anotherObject);
    void collisionWithOpponent(Opponent *opponent);
    void collisionWithObstacle(Obstacle *obstacle);
    void collisionWithDefense(Defense *defense);
    void collisionWithBullet(Bullet *bullet);
    void doAction(Play *play);
public:
    static const int DEFENSE_CODE = 9;
    Defense(GameField *gameField, int hp);// przy konstruktorach defense, opponent, obstacle daje w argumentach wskaznik na gamefield by znac pole w ktorym chce narysowac
    Defense(GameField *gameField, ifstream *inputStream);

    void displayOnConsole();
    ~Defense();
    void saveToStream(ofstream* outputStream);
};

#endif