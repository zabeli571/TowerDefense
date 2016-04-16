#include "CreatorButton.h"

CreatorButton::CreatorButton(int number, int code, string name) : Button(BUTTON_XPOS, BUTTON_YPOS+number*BUTTON_SPACE, BUTTON_WIDTH, BUTTON_HEIGHT, code,  name) {
    cout<<"\tkonstruktor CreatorButton"<<endl;
    allegroColor = al_map_rgb( 0,  102, 102);
}

CreatorButton::~CreatorButton()
{
    cout<<"destruktor CreatorButton"<<endl;
}



