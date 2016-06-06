#ifndef TOWERDEFENSE_PROGRESSFIELD_H
#define TOWERDEFENSE_PROGRESSFIELD_H


#include "MainObject.h"

class ProgressField : public MainObject{
private:
    int progress = 100;
public:
    ProgressField(int x, int y, int xLength, int yLength);
    ~ProgressField();
    void draw();

    void setProgress(int i);

    int getProgress();
};


#endif //TOWERDEFENSE_PROGRESSFIELD_H
