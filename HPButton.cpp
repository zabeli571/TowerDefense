#include "HPButton.h"

HPButton::HPButton(int number, int code, string name) : Button(BUTTON_XPOS+number*BUTTON_SPACE, BUTTON_YPOS, BUTTON_WIDTH, BUTTON_HEIGHT, code,  name)
{
    cout<<"\tkonstruktor HPButton"<<endl;
    allegroColor = al_map_rgb(255,  153, 153);
    fontSize=yLength-30;
    font=al_load_ttf_font("fonts/font3.ttf",fontSize,0);
}

HPButton::~HPButton()
{
    cout<<"destruktor HPButton"<<endl;
}



