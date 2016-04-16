#include "MenuButton.h"

MenuButton::MenuButton(int number, int code, string name) : Button(BUTTON_XPOS, BUTTON_YPOS+number*BUTTON_SPACE, BUTTON_WIDTH, BUTTON_HEIGHT, code,  name) {
    cout<<"\tkonstruktor MenuButton"<<endl;
    allegroColor = al_map_rgb( 0,  102, 102);
}

MenuButton::~MenuButton()
{
    cout<<"destruktor MenuButton"<<endl;
}



