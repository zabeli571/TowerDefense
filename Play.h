#ifndef TOWERDEFENSE_PLAY_H
#define TOWERDEFENSE_PLAY_H

#include "GameObject.h"
class Game;

class Play {
private:
    static const int REFRESH_TIME = 50;

    vector<GameObject*> *gameObjects; //wskaznik na wektor GameObjectow
    Game *game;

    void deleteObject(GameObject *gameObject);
    bool checkForOutsideField();
    bool checkForWin();
public:
    static const int VICTORY_CODE = 1;
    static const int DEFEAT_CODE = 0;

    void addObject(GameObject *gameObject);
    Play(Game *game,vector<GameObject*> *gameObjects);
    ~Play();
    int run();

};


#endif //TOWERDEFENSE_PLAY_H
