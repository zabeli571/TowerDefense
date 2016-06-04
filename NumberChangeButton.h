#ifndef TOWERDEFENSE_NUMBERCHANGEBUTTON_H
#define TOWERDEFENSE_NUMBERCHANGEBUTTON_H


#include <iostream>
#include <allegro5/allegro.h>
#include "Constants.h"
#include "Button.h"

using namespace std;

class NumberChangeButton : public Button
{
private:
    static const int BUTTON_WIDTH=60;
    static const int BUTTON_HEIGHT=50;
public:
    static const int NUMBER_CHANGE_BUTTON_INCREASE_MONEY = 10000;
    static const int NUMBER_CHANGE_BUTTON_DECREASE_MONEY = 10001;
    static const int NUMBER_CHANGE_BUTTON_INCREASE_WAVES = 10002;
    static const int NUMBER_CHANGE_BUTTON_DECREASE_WAVES = 10003;
    static const int NUMBER_CHANGE_BUTTON_INCREASE_FREQUENCY = 10004;
    static const int NUMBER_CHANGE_BUTTON_DECREASE_FREQUENCY = 10005;
    NumberChangeButton(int x,int y ,int code, bool isUp);
    ~NumberChangeButton();
};


#endif //TOWERDEFENSE_NUMBERCHANGEBUTTON_H
