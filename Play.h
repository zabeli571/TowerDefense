#ifndef TOWERDEFENSE_PLAY_H
#define TOWERDEFENSE_PLAY_H

#include "GameObject.h"
class Game;

class Play {
private:
    static const int REFRESH_TIME = 50;

    vector<GameObject*> *gameObjects; //wskaznik na wektor GameObjectow
    Game *game;
public:
    void addBullet(int column, int row);
    Play(Game *game,vector<GameObject*> *gameObjects);
    ~Play();
    void run();

    void deleteDyingObject(GameObject *gameObject);
};


#endif //TOWERDEFENSE_PLAY_H
