#ifndef TOWERDEFENSE_STATISTICS_H
#define TOWERDEFENSE_STATISTICS_H

#include "MainObject.h"
#include "GameObject.h"
#include "Button.h"
#include <cstdio>

class Statistics : MainObject
{
private:
    static const int POINTS_PER_OPPONENT = 10;
    static const int POINTS_PER_OBSTACLE = 20;
    static const int POINTS_PER_DEFENSE = 10;

    Button *backButton;

    ALLEGRO_FONT *font;
    int fontSize;

    int points, opponentsDefeated, obstaclesStand, defensesStand;

    int sumPoints();
    string createPointsString(int item, int pointsPerItem);
public:
    static const int BACK_CODE = 0;
    static const int NEXT_LEVEL_CODE = 1;

    Statistics();
    ~Statistics();
    void draw();
    void setPlayFinished(int code);
    void addOpponentDefeated();
    void countDefendersStand(vector<GameObject*> *gameObjects);
    int getButtonCodeWhenClicked();
};


#endif //TOWERDEFENSE_STATISTICS_H
