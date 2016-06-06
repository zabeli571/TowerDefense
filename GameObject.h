#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <fstream>
#include <chrono>
#include "MainObject.h"
#include "GameField.h"

class Opponent;
class Obstacle;
class Defense;
class Bullet;
class Play;

class GameObject : public MainObject
{
private:
    static int idCounter;

    static int getNextId();
protected:
    ALLEGRO_BITMAP *imageHalfHP;
    GameField *gameField;
    int gridXPos, gridYPos, gridXPosPx, gridYPosPx, id;
public:
    int hp,initialHP;
    bool willMove;

    static void resetIdCounter();
    static int getCurrentId();
    static int setCurrentId(int idCounter);

    static GameObject* getGameObjectByCode(GameField *gameField,int code, ifstream *inputStream);
    static GameObject *loadGameObjectByCode(GameField *gameField, int code, ifstream *inputStream);

    GameObject(GameField *gameField);
    GameObject(GameField *gameField, int row, int column);
    GameObject(GameField *gameField, int x, int y, bool exact);
    GameObject(GameField *gameField, ifstream *inputStream);
    GameObject(GameField *gameField, ifstream *inputStream, bool exact);
    ~GameObject();
    void draw();
    virtual void displayOnConsole();
    bool isItsPosition(int randomRow,int randomColumn);//dla kazdego obiektu sprawdzam cz wylosowane pole to jego pozycja
    virtual void saveToStream(ofstream* outputStream);
    virtual void saveToStreamExact(ofstream* outputStream);

    virtual void collisionWith(GameObject *anotherObject) = 0;
    virtual void collisionWithOpponent(Opponent *opponent) = 0;
    virtual void collisionWithObstacle(Obstacle *obstacle) = 0;
    virtual void collisionWithDefense(Defense *defense) = 0;
    virtual void collisionWithBullet(Bullet *bullet) = 0;
    virtual void doAction(Play *play) = 0;
    virtual void move() = 0;

    virtual void managePauseStart(chrono::milliseconds pauseStartTime);
    virtual void managePauseEnd(chrono::milliseconds pauseEndTime);
    bool willDie();

    static bool areObjectsClashed(GameObject *first, GameObject *second);

    bool isOutsideField();
};

#endif //TOWERDEFENSE_GAMEOBJECT_H
