#ifndef GAME_FIELD_H
#define GAME_FIELD_H
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "MainObject.h"
#include "Constants.h"
#include <cstdlib>
#include <ctime>

using namespace std;

class GameField: public MainObject
{
    friend class GameObject;
private:
    static const int CREATOR_XPOS=50;
    static const int CREATOR_YPOS=40;
    static const int CREATOR_WIDTH=600;
    static const int CREATOR_HEIGHT=300;
    static const int CREATOR_ROWS=5;
    static const int CREATOR_COLUMNS=10;

    static const int PLAY_XPOS=100;
    static const int PLAY_YPOS=50;
    static const int PLAY_WIDTH=800;
    static const int PLAY_HEIGHT=400;
    static const int PLAY_ROWS=5;
    static const int PLAY_COLUMNS=10;

    int rows,columns;

    int getSquareSize();
public:
    static const int GAME_FIELD_CREATOR_CODE = 12;
    static const int GAME_FIELD_PLAY_CODE = -12;

    GameField(int code);
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
