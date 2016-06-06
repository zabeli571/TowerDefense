#ifndef OPPONENT_H
#define OPPONENT_H

#include <iostream>
#include <allegro5/allegro.h>
#include <iostream>
#include <allegro5/allegro.h>
#include "MainObject.h"
#include "GameObject.h"


using namespace std;

class Opponent: public GameObject
{
protected:
    static const int ATTACK_INTERVAL = 1000;
    static const int FREEZE_INTERVAL = 3000;
    chrono::milliseconds lastAttackTime;
    int toNextAttackTime;
    int toDefrostTime;

    long long int freezeTimeStamp = 0;

    void move();
    void collisionWith(GameObject *anotherObject);
    void collisionWithOpponent(Opponent *opponent);
    void collisionWithObstacle(Obstacle *obstacle);
    void collisionWithDefense(Defense *defense);
    void collisionWithBullet(Bullet *bullet);
    void doAction(Play *play);

public:
    static const int OPPONENT_CODE = 10;
    void displayOnConsole();
    Opponent(GameField *gameField);
    Opponent(GameField *gameField, int row, int column);
    Opponent(GameField *gameField, ifstream *inputStream);
    void saveToStream(ofstream* outputStream);
    ~Opponent();
    void freeze();

    virtual void managePauseStart(chrono::milliseconds pauseStartTime);
    virtual void managePauseEnd(chrono::milliseconds pauseEndTime);
};

#endif