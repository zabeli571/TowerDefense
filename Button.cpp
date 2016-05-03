#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "Button.h"

using namespace std;

Button:: Button(int x, int y, int xLength, int yLength, int code, string name)
{
    cout<<"\tkonstruktor Button "<< endl<<"\t";
    this->x=x;
    this->y=y;
    this->xLength=xLength;
    this->yLength=yLength;
    this->code=code;
    this->name=name;
    fontSize=yLength-12;
    font=al_load_ttf_font("fonts/font1.ttf",fontSize,0);
    allegroColor = al_map_rgb( 0,  102, 102);
}

void Button:: draw()
{
    al_draw_filled_rounded_rectangle(x, y, x+xLength, y+yLength, 25, 25, allegroColor);
    al_draw_text(font, al_map_rgba(255,  229, 204,128),x+xLength/2,y+yLength/2-fontSize/2-2,ALLEGRO_ALIGN_CENTRE,name.c_str());
}

Button:: ~Button(){
    cout<<"\tdestruktor Button"<<endl<<"\t";
}


