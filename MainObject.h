#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

using namespace std;

class MainObject
{
protected:
    ALLEGRO_COLOR allegroColor;
    ALLEGRO_BITMAP *image;
    int x, y, xLength, yLength;
    int clickXPos, clickYPos;
    int code=0;
public:
    virtual void draw()=0;
    int getCodeIfClicked(int x, int y, MainObject **clickedObject);
    void changeColor(ALLEGRO_COLOR color);
    MainObject();
    virtual ~MainObject();
    int getCode();
};

#endif //TOWERDEFENSE_MAINOBJECT_H
