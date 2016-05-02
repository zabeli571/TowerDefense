#ifndef OPPONENT_H
#define OPPONENT_H

#include <iostream>
#include <allegro5/allegro.h>
#include <iostream>
#include <allegro5/allegro.h>
#include "MainObject.h"
#include "GameObject.h"
#include "GameField.h"



using namespace std;

class Opponent: public GameObject//spis tresci
{
public:
    static const int OPPONENT_CODE = 10;
    void displayOnConsole();
    Opponent(GameField *gameField);
    Opponent(GameField *gameField, int row, int column);
    void saveToStream(ofstream* outputStream);
    void createFromStream(ifstream* inputStream);
    ~Opponent();
};

#endif