#ifndef TOWERDEFENSE_LEGEND_H
#define TOWERDEFENSE_LEGEND_H

#include <iostream>
#include <allegro5/allegro.h>
#include <iostream>
#include <allegro5/allegro.h>
#include "MainObject.h"
#include "GameObject.h"
#include "GameField.h"
#include <allegro5/allegro_image.h>

using namespace std;

class Legend: public MainObject
{
public:
    Legend();
    void draw();
   // ~Legend();
};


#endif //TOWERDEFENSE_LEGEND_H
