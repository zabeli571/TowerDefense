#ifndef TOWERDEFENSE_NUMBERFIELD_H
#define TOWERDEFENSE_NUMBERFIELD_H

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "MainObject.h"

using namespace std;

class NumberField :public MainObject
{
protected:
    int fontSize;
    ALLEGRO_FONT *font;
    int *number;
public:
    NumberField(int x, int y, int fontSize ,int *number);
    ~NumberField();
    void draw();
};



#endif //TOWERDEFENSE_NUMBERFIELD_H
