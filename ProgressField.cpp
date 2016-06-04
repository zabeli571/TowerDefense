#include "ProgressField.h"
using namespace std;

ProgressField:: ProgressField(int x, int y, int xLength, int yLength)
{
    cout<<"\tkonstruktor ProgressField "<< endl<<"\t";
    this->x=x;
    this->y=y;
    this->xLength=xLength;
    this->yLength=yLength;
    allegroColor = al_map_rgb( 0,  102, 102);
}

void ProgressField:: draw()
{
    al_draw_rectangle(x, y, x+xLength, y+yLength,allegroColor,5);
    al_draw_filled_rectangle(x, y, x+(xLength*((double)progress/100)), y+yLength, allegroColor);
}

ProgressField:: ~ProgressField(){
    cout<<"\tdestruktor ProgressField"<<endl<<"\t";
}

void ProgressField::setProgress(int progress) {
    this->progress = progress;
}


