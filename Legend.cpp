#include "Legend.h"

Legend::Legend()
{
    x = 50;
    y = 400;
    xLength = 300;
    yLength = 200;
    image = al_load_bitmap("layouts/legend.png");
    cout<<"\tkonstruktor Legend"<<endl;
}

void Legend::draw()
{
    al_draw_scaled_bitmap(image,0,0,al_get_bitmap_width(image), al_get_bitmap_height(image),x,y,xLength,yLength,0);
}



