#ifndef GAME_FIELD_H
#define GAME_FIELD_H
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include "MainObject.h"
#include "Constants.h"
#include <cstdlib>
#include <ctime>

using namespace std;

class GameField: public MainObject
{
private:
    static const int GAME_FIELD_XPOS=50;
    static const int GAME_FIELD_YPOS=90;
    static const int GAME_FIELD_WIDTH=600;
    static const int GAME_FIELD_HEIGHT=300;
    static const int GAME_FIELD_SQUARE=60;
    static const int GAME_FIELD_ROWS=5;
    static const int GAME_FIELD_COLUMNS=10;
public:
    static const int GAME_FIELD_CODE = 12;
    GameField();
    virtual ~GameField();
    void getProperties(int *x, int *y, int *sq);//gamefield xpos, ypos,szerokosc kwadratu
    void draw();
    void whichSquare(int *x,int *y, int *row, int *column);//ktory zostal klikniety
    void getRandomSquare(int *row, int *column);//losuje kwadracik
    void changeStateToActive();//pole rozowe
    void changeStateToInactive();//pole niebieskie
    void getSquareRelativePos(int row, int column, int *xRelativePos, int *yRelativePos);//wzgledem okna gry
    int getSquareCount();//wielkosc pola - 50 kwadracikow
};

#endif //TOWERDEFENSE_GAMEFIELD_H
