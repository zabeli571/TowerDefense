#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "MainObject.h"
#include "GameField.h"
#include <fstream>

class GameObject : public MainObject
{
protected:
    int gridXPos, gridYPos, gridXPosPx, gridYPosPx;

public:
    static GameObject* getGameObjectByCode(GameField *gameField,int code, ifstream *inputStream);
    GameObject(GameField *gameField);
    GameObject(GameField *gameField, int row, int column);
    GameObject(GameField *gameField, ifstream *inputStream);
    ~GameObject();
    void draw();
    virtual void displayOnConsole();
    bool isItsPosition(int randomRow,int randomColumn);//dla kazdego obiektu sprawdzam cz wylosowane pole to jego pozycja
    virtual void saveToStream(ofstream* outputStream);
};

#endif //TOWERDEFENSE_GAMEOBJECT_H
