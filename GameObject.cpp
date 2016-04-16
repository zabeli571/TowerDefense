#include "GameObject.h"

GameObject::GameObject(GameField *gameField)
{
    cout<<"\tkonstruktor GameObject"<<endl<<"\t";
    int xRelative,yRelative,row,column;//wzgledem pola gry, nie window
    gameField->whichSquare(&xRelative,&yRelative,&row,&column);
    gridXPos = column;
    gridYPos = row;
    gridXPosPx=xRelative;
    gridYPosPx=yRelative;
    int gameFieldX, gameFieldY, squareWidth;// polozenie pola gry wzgledem okna i szerokosc kwadratu
    gameField->getProperties(&gameFieldX,&gameFieldY,&squareWidth);//zapisuje w polach na ktore wskazuja te adresy
    xLength = squareWidth;
    yLength = squareWidth;
    x=gameFieldX+gridXPosPx;
    y=gameFieldY+gridYPosPx;
}

GameObject::GameObject(GameField *gameField, int row, int column)//drugi konstruktor dla obstacle i opponent
{
    cout<<"\tkonstruktor GameObject"<<endl<<"\t";
    int xRelative,yRelative;
    gameField->getSquareRelativePos(row,column,&xRelative,&yRelative);
    gridXPos = column;
    gridYPos = row;
    gridXPosPx=xRelative;
    gridYPosPx=yRelative;
    int gameFieldX, gameFieldY, squareWidth;
    gameField->getProperties(&gameFieldX,&gameFieldY,&squareWidth);
    xLength = squareWidth;
    yLength = squareWidth;
    x=gameFieldX+gridXPosPx;
    y=gameFieldY+gridYPosPx;
}


void GameObject::draw()
{
    al_draw_filled_rectangle(x+1, y+1, x+xLength-1, y+yLength-1, allegroColor);
}

bool GameObject::isItsPosition(int randomRow, int randomColumn)
{
    return randomRow == gridYPos && randomColumn == gridXPos;//obiekt posiada juz o sobie te informacje w atrybutach
}

void GameObject::displayOnConsole()
{
    cout<<"\tGameObject, pozycja: X " << gridXPos << ", Y: "<<gridYPos<<endl;
}

GameObject::~GameObject()
{
    cout<<"\tdestruktor GameObject"<<endl<<"\t";
}








