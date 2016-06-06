#ifndef TOWERDEFENSE_PAUSE_H
#define TOWERDEFENSE_PAUSE_H


#include <list>
#include "MainObject.h"
#include "Button.h"

class Pause : MainObject {

private:
    list<Button*> buttons;//tylko defense,opponents,obstacles
public:
    static const int BACK_CODE = 1;
    static const int SAVE_CODE = 2;
    static const int EXIT_CODE = 3;

    Pause();
    ~Pause();
    void draw();
    int getButtonCodeWhenClicked(); //zwroci back_code gdy wybiore przycisk powrot
};


#endif //TOWERDEFENSE_PAUSE_H
