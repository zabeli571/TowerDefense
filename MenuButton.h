#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include "Constants.h"
#include "Button.h"
using namespace std;

class MenuButton : public Button
{
private:
    static const int BUTTON_XPOS=Constants::WINDOW_WIDTH/2-120;
    static const int BUTTON_YPOS=110;
    static const int BUTTON_WIDTH=240;
    static const int BUTTON_HEIGHT=60;
    static const int BUTTON_SPACE=80;
public:
    static const int MENU_BUTTON_CODE_NEW_GAME = 1;
    static const int MENU_BUTTON_CODE_LOAD_GAME = 2;
    static const int MENU_BUTTON_CODE_CREATE_MAP = 3;
    static const int MENU_BUTTON_CODE_LEGEND = 4;
    static const int MENU_BUTTON_CODE_EXIT = 5;
    MenuButton(int number, int code, string name);
    ~MenuButton();
};
#endif

