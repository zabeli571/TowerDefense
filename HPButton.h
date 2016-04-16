#ifndef TOWERDEFENSE_HPBUTTON_H
#define TOWERDEFENSE_HPBUTTON_H

#include <iostream>
#include <allegro5/allegro.h>
#include "Constants.h"
#include "Button.h"

class HPButton : public Button
{
private:
    static const int BUTTON_XPOS = Constants::WINDOW_WIDTH / 2 - 300;
    static const int BUTTON_YPOS = 450;
    static const int BUTTON_WIDTH = 80;
    static const int BUTTON_HEIGHT = 50;
    static const int BUTTON_SPACE = 90;
public:
    static const int HP_BUTTON_CODE_HP6= 13;
    static const int HP_BUTTON_CODE_HP8 = 14;
    static const int HP_BUTTON_CODE_HP10 = 15;
    HPButton(int number, int code, string name);
    ~HPButton();
};
#endif //TOWERDEFENSE_HPBUTTON_H
