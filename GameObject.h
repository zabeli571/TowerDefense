#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "MainObject.h"
#include "GameField.h"

class GameObject : public MainObject
{
protected:
    int gridXPos, gridYPos, gridXPosPx, gridYPosPx;
public:
    GameObject(GameField *gameField);
    GameObject(GameField *gameField, int row, int column);
    ~GameObject();
    void draw();
    virtual void displayOnConsole();
    bool isItsPosition(int randomRow,int randomColumn);//dla kazdego obiektu sprawdzam cz wylosowane pole to jego pozycja
};

#endif //TOWERDEFENSE_GAMEOBJECT_H
