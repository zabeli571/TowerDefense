#ifndef TOWERDEFENSE_LEGEND_H
#define TOWERDEFENSE_LEGEND_H


#include "MainObject.h"
#include "GameObject.h"
#include "Button.h"


class Legend : MainObject {
private:
    Button *backButton;
public:
    static const int BACK_CODE = 1;

    Legend();
    ~Legend();
    void draw();
    int getButtonCodeWhenClicked(); //zwroci back_code gdy wybiore przycisk powrot
};
#endif //TOWERDEFENSE_LEGEND_H
