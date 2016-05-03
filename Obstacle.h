#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <iostream>
#include <allegro5/allegro.h>
#include <iostream>
#include <allegro5/allegro.h>
#include "MainObject.h"
#include "GameObject.h"

using namespace std;

class Obstacle: public GameObject
{
private:
    void move();
    void collisionWith(GameObject *anotherObject);
    void collisionWithOpponent(Opponent *opponent);
    void collisionWithObstacle(Obstacle *obstacle);
    void collisionWithDefense(Defense *defense);
    void doAction();
public:
    static const int OBSTACLE_CODE = 11;
    void displayOnConsole();
    Obstacle(GameField *gameField);//przekazuje do konstruktora i tam z niego korzystam
    Obstacle(GameField *gameField, int row, int column);
    Obstacle(GameField *gameField, ifstream *inputStream);

    ~Obstacle();
    void saveToStream(ofstream* outputStream);
};



#endif //TOWERDEFENSE_OBSTACLE_H
