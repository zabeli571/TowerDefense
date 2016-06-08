#ifndef TOWERDEFENSE_STATISTICS_H
#define TOWERDEFENSE_STATISTICS_H

#include "MainObject.h"
#include "GameObject.h"
#include <cstdio>
#include <list>

class Button;

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
    //static const int NEXT_LEVEL_CODE = 1;

    Statistics();
    ~Statistics();
    void draw();
    void setPlayFinished(int code); //zaladuje bitmape wygranej lub przegranej
    void addOpponentDefeated(); //dodaje kolejnego pokonanego przeciwnika
    void countDefendersStand(list<GameObject*> *gameObjects); //zliczam obstacle i defense, ktore przezyly
    int getButtonCodeWhenClicked(); //zwroci back_code gdy wybiore przycisk powrot
    int getOpponentsDefeated();
    void setOpponentsDefeated(int opponentsCount);
};


#endif //TOWERDEFENSE_STATISTICS_H
