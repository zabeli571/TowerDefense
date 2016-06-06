#include "MainObject.h"

int MainObject::getCodeIfClicked(int x, int y, MainObject **clickedObject)
{
    if(x>this->x && x<this->x+xLength && y>this->y && y<this->y+yLength)
    {
        clickXPos=x;//state.x
        clickYPos=y;
        if(clickedObject != NULL)
        {
            *clickedObject=this;//this tzn ten gameobjects[i], w ktorym jestesmy teraz
        }
        return code;
    }
    else
        return 0;
}

MainObject::~MainObject()
{
//    cout << "\tdestruktor MainObject "<<endl;
    delete(image);
}

int MainObject::getCode()
{
    return code;
}

void MainObject::changeColor(ALLEGRO_COLOR color) {
    allegroColor = color;
}

MainObject::MainObject()
{
//    cout<<"konstruktor MainObject"<<endl;
}

void MainObject::setState(int state)
{
    this->state = state;
}

int MainObject::getState()
{
    return state;
}












