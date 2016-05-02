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
public:
    static const int OBSTACLE_CODE = 11;
    void displayOnConsole();
    Obstacle(GameField *gameField);//przekazuje do konstruktora i tam z niego korzystam
    Obstacle(GameField *gameField, int row, int column);
    ~Obstacle();
    void saveToStream(ofstream* outputStream);
    void createFromStream(ifstream* inputStream);
};



#endif //TOWERDEFENSE_OBSTACLE_H
