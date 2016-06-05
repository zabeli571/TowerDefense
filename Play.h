#ifndef TOWERDEFENSE_PLAY_H
#define TOWERDEFENSE_PLAY_H

#include "GameObject.h"
#include "Statistics.h"
#include "ProgressField.h"
#include "GameObjectSelector.h"

class Game;

class Play
{
private:
    static const int REFRESH_TIME = 50;

    GameField *gameField;
    vector<GameObject*> *gameObjects; //wskaznik na wektor wskaznikow na GameObjecty
    vector<MainObject*> *interfaceObjects; //wskaznik na wektor wskaznikow na GameObjecty
    vector<GameObjectSelector*> gameObjectsSelectors; //wskaznik na wektor wskaznikow na GameObjecty
    Game *game;
    Statistics *statistics; //wskaznik na obiekt statistics
    int money = 0, waves = 0,frequency = 0;
    MainObject *clickedObject;
    ProgressField *progressField;
    long long int lastWaveTime = (std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch())).count();
    int addGameObjectCode = 0;

    void deleteObject(GameObject *gameObject);
    bool checkForOutsideField();
    bool checkForWin();
    void drawPlay();
    void loadObjects(string mapName);
    void manageMouseClicked(ALLEGRO_MOUSE_STATE *state);
    bool getCodeIfClicked(ALLEGRO_MOUSE_STATE *state, int *codePointer);
    void manageWaveReady(long long int);
    void createWave();
    void manageGameObjectSelectorsState();
    GameObjectSelector* getSelectorByCode();
    GameObjectSelector *getSelectorByClicked();
    void increaseMoneyForDefeatingOpponent(int code);

public:
    static const int VICTORY_CODE = 1;
    static const int DEFEAT_CODE = 0;

    Play(string mapName ,Game *game,vector<GameObject*> *gameObjects, vector<MainObject*> *interfaceObjects ,Statistics *statistics);
    ~Play();
    void addObject(GameObject *gameObject);
    int run();

};


#endif //TOWERDEFENSE_PLAY_H
