#ifndef TOWERDEFENSE_OPPONENTSHOOT_H
#define TOWERDEFENSE_OPPONENTSHOOT_H

#include <iostream>
#include <allegro5/allegro.h>
#include "MainObject.h"
#include "GameObject.h"
#include "Opponent.h"

class OpponentShoot : public Opponent
{
private:
    static const int SHOOT_INTERVAL = 3000;
    chrono::milliseconds lastShootTime;

protected:
    void doAction(Play *play);
public:
    static const int OPPONENT_SHOOT_CODE = 103;


    OpponentShoot(GameField *gameField);
    OpponentShoot(GameField *gameField,  int row, int column);
    OpponentShoot(GameField *gameField, ifstream *inputStream);

    void displayOnConsole();
    ~OpponentShoot();
};
#endif //TOWERDEFENSE_OPPONENTSHOOT_H
