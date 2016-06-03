#ifndef TOWERDEFENSE_PLAY_H
#define TOWERDEFENSE_PLAY_H

#include "GameObject.h"
#include "Statistics.h"

class Game;

class Play
{
private:
    static const int REFRESH_TIME = 50;

    vector<GameObject*> *gameObjects; //wskaznik na wektor wskaznikow na GameObjecty
    Game *game;
    Statistics *statistics; //wskaznik na obiekt statistics

    void deleteObject(GameObject *gameObject);
    bool checkForOutsideField();
    bool checkForWin();
public:
    static const int VICTORY_CODE = 1;
    static const int DEFEAT_CODE = 0;

    Play(Game *game,vector<GameObject*> *gameObjects,Statistics *statistics);
    ~Play();
    void addObject(GameObject *gameObject);
    int run();

};


#endif //TOWERDEFENSE_PLAY_H
