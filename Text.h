#ifndef TOWERDEFENSE_TEXT_H
#define TOWERDEFENSE_TEXT_H

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "MainObject.h"

using namespace std;

class Text :public MainObject
{
private:
    string text;
    int alignFlag;
    ALLEGRO_FONT *font;

public:
    Text(int x, int y, int fontSize ,string text,int alignFlag);
    ~Text();
    void draw();
};


#endif //TOWERDEFENSE_TEXT_H
