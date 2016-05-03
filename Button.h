#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "MainObject.h"

using namespace std;

class Button :public MainObject
{
protected:
    int fontSize;
    string name;
    ALLEGRO_FONT *font;
public:
    static const int BUTTON_PLAY_START = 110;

    Button(int x, int y, int xLength, int yLength, int code, string name);
    ~Button();
    void draw();
};
#endif


