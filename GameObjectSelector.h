#ifndef TOWERDEFENSE_GAMEOBJECTSELECTOR_H
#define TOWERDEFENSE_GAMEOBJECTSELECTOR_H


#include "MainObject.h"

class GameObjectSelector : public MainObject {
private:
    int price;
    int gameObjectCode;
    ALLEGRO_BITMAP *imageDisabled;
public:
    static const int GAME_OBJECT_SELECTOR_CODE_DEFENSE = 20002;
    static const int GAME_OBJECT_SELECTOR_CODE_DEFENSE_ICE = 200022;
    static const int GAME_OBJECT_SELECTOR_CODE_DEFENSE_WALK = 2000222;
    static const int GAME_OBJECT_SELECTOR_CODE_OBSTACLE = 20003;

    GameObjectSelector(int x, int y, int xLength, int yLength, int code);
    ~GameObjectSelector();
    void draw();
    int getPrice();
    int getGameObjectCode();
};
#endif //TOWERDEFENSE_GAMEOBJECTSELECTOR_H
