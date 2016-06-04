#include "NumberField.h"
using namespace std;

NumberField:: NumberField(int x, int y, int fontSize ,int* number)
{
    cout<<"\tkonstruktor NumberField "<< endl<<"\t";
    this->x=x;
    this->y=y;
    this->xLength=0;
    this->yLength=0;
    this->fontSize=fontSize;
    this->number = number;
    font=al_load_ttf_font("fonts/font3.ttf",fontSize,0);
    allegroColor = al_map_rgb( 0,  102, 102);
}

void NumberField:: draw()
{
    al_draw_text(font, al_map_rgba(255,  229, 204,128),x,y,ALLEGRO_ALIGN_CENTRE,to_string(*number).c_str());
}

NumberField:: ~NumberField(){
    cout<<"\tdestruktor NumberField"<<endl<<"\t";
}
