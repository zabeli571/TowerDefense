#include "Text.h"
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

using namespace std;

Text:: Text(int x, int y, int fontSize ,string text,int alignFlag)
{
    cout<<"\tkonstruktor Text "<< endl<<"\t";
    this->x=x;
    this->y=y;
    this->xLength=0;
    this->yLength=0;
    this->text = text;
    this->alignFlag = alignFlag;
    font=al_load_ttf_font("fonts/font1.ttf",fontSize,0);
    allegroColor = al_map_rgb( 0,  102, 102);
}

void Text:: draw()
{
    al_draw_text(font, al_map_rgba(255,  229, 204,128),x,y,alignFlag,text.c_str());
}

Text:: ~Text(){
    cout<<"\tdestruktor Text"<<endl<<"\t";
}
