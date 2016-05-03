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
private:
    static const int ATTACK_INTERVAL = 1000;
    chrono::milliseconds lastAttackTime;

    void move();
    void collisionWith(GameObject *anotherObject);
    void collisionWithOpponent(Opponent *opponent);
    void collisionWithObstacle(Obstacle *obstacle);
    void collisionWithDefense(Defense *defense);
    void doAction();

public:
    static const int OPPONENT_CODE = 10;
    void displayOnConsole();
    Opponent(GameField *gameField);
    Opponent(GameField *gameField, int row, int column);
    Opponent(GameField *gameField, ifstream *inputStream);
    void saveToStream(ofstream* outputStream);
    ~Opponent();
};

#endif