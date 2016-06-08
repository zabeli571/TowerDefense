#ifndef CREATOR_BUTTON_H
#define CREATOR_BUTTON_H
#include <iostream>
#include <allegro5/allegro.h>
#include "Button.h"
#include "Game.h"

using namespace std;

class Game;

class CreatorButton : public Button
{
private:
    static const int BUTTON_XPOS=Game::WINDOW_WIDTH/2+200;
    static const int BUTTON_YPOS=30;
    static const int BUTTON_WIDTH=240;
    static const int BUTTON_HEIGHT=50;
    static const int BUTTON_SPACE=60;
public:
    static const int CREATOR_BUTTON_CODE_ADD_TOWER = 1;
    static const int CREATOR_BUTTON_CODE_ADD_OPPONENT = 2;
    static const int CREATOR_BUTTON_CODE_ADD_OBSTACLE = 3;
    static const int CREATOR_BUTTON_CODE_REMOVE_OBJECT=4;
    static const int CREATOR_BUTTON_CODE_RANDOM_OPPONENT = 5;
    static const int CREATOR_BUTTON_CODE_RANDOM_OBSTACLE = 6;
    static const int CREATOR_BUTTON_CODE_SAVE = 7;
    static const int CREATOR_BUTTON_CODE_RETURN = 8;
    static const int CREATOR_BUTTON_CODE_DISPLAY = 16;
    CreatorButton(int number, int code, string name);
    ~CreatorButton();
};
#endif