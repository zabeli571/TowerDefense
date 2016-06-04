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
    int state = STATE_CODE_NORMAL;
public:
    static const int STATE_CODE_NORMAL = 0;
    static const int STATE_CODE_CLICKED = 1;
    static const int STATE_CODE_DISABLED = 2;

    virtual void draw()=0;
    int getCodeIfClicked(int x, int y, MainObject **clickedObject);
    void changeColor(ALLEGRO_COLOR color);
    MainObject();
    virtual ~MainObject();
    int getCode();
    void setState(int state);
    int getState();
};

#endif //TOWERDEFENSE_MAINOBJECT_H
