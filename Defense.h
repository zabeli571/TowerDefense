#ifndef DEFENSE_H
#define DEFENSE_H

#include <iostream>
#include <allegro5/allegro.h>
#include "MainObject.h"
#include "GameObject.h"

using namespace std;

class Defense: public GameObject
{
protected:
    static const int ATTACK_INTERVAL = 3000;
    chrono::milliseconds lastAttackTime;
    int toNextAttackTime;

    void move();
    void collisionWith(GameObject *anotherObject);
    void collisionWithOpponent(Opponent *opponent);
    void collisionWithObstacle(Obstacle *obstacle);
    void collisionWithDefense(Defense *defense);
    void collisionWithBullet(Bullet *bullet);
    void doAction(Play *play);
public:
    static const int DEFENSE_CODE = 9;
    Defense(GameField *gameField);// przy konstruktorach defense, opponent, obstacle daje w argumentach wskaznik na gamefield by znac pole w ktorym chce narysowac
    Defense(GameField *gameField, ifstream *inputStream);
    Defense(GameField *gameField, ifstream *inputStream,bool exact);

    void displayOnConsole();
    ~Defense();
    void saveToStream(ofstream* outputStream);
    virtual void managePauseStart(chrono::milliseconds pauseStartTime);
    virtual void managePauseEnd(chrono::milliseconds pauseEndTime);

    void saveToStreamExact(ofstream* outputStream);
};

#endif