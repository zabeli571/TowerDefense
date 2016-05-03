#ifndef TOWERDEFENSE_PLAY_H
#define TOWERDEFENSE_PLAY_H

#include "GameObject.h"
class Game;

class Play {
    friend class Defence;
private:
    static const int REFRESH_TIME = 100;

    vector<GameObject*> *gameObjects;
    Game *game;
public:
    Play(Game *game,vector<GameObject*> *gameObjects);
    ~Play();
    void run();

    void deleteDyingObject(GameObject *gameObject);
};


#endif //TOWERDEFENSE_PLAY_H
