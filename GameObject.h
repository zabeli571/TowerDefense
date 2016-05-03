#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <fstream>
#include <chrono>
#include "MainObject.h"
#include "GameField.h"

class Opponent;
class Obstacle;
class Defense;

class GameObject : public MainObject
{
private:
    static int idCounter;

    static int getNextId();
protected:
    int gridXPos, gridYPos, gridXPosPx, gridYPosPx, id;
public:
    int hp;
    bool willMove;

    static void resetIdCounter();
    static GameObject* getGameObjectByCode(GameField *gameField,int code, ifstream *inputStream);
    GameObject(GameField *gameField);
    GameObject(GameField *gameField, int row, int column);
    GameObject(GameField *gameField, ifstream *inputStream);
    ~GameObject();
    void draw();
    virtual void displayOnConsole();
    bool isItsPosition(int randomRow,int randomColumn);//dla kazdego obiektu sprawdzam cz wylosowane pole to jego pozycja
    virtual void saveToStream(ofstream* outputStream);

    virtual void collisionWith(GameObject *anotherObject) = 0;
    virtual void collisionWithOpponent(Opponent *opponent) = 0;
    virtual void collisionWithObstacle(Obstacle *obstacle) = 0;
    virtual void collisionWithDefense(Defense *defense) = 0;
    virtual void doAction() = 0;
    virtual void move() = 0;
    bool willDie();

    static bool areObjectsClashed(GameObject *first, GameObject *second);
};

#endif //TOWERDEFENSE_GAMEOBJECT_H
