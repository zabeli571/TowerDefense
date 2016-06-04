#include "NumberChangeButton.h"

NumberChangeButton::NumberChangeButton(int x,int y ,int code, bool isUp) : Button(x, y, BUTTON_WIDTH, BUTTON_HEIGHT, code,  isUp?"+":"-") {
    cout<<"\tkonstruktor NumberChangeButton"<<endl;
    allegroColor = al_map_rgb( 0,  102, 102);
    font=al_load_ttf_font("fonts/font2.ttf",fontSize,0);
}

NumberChangeButton::~NumberChangeButton()
{
    cout<<"destruktor NumberChangeButton"<<endl;
}



