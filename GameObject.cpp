#include "GameObject.h"
#include "Opponent.h"
#include "Obstacle.h"
#include "Defense.h"
#include "DefenseIce.h"
#include "DefenseWalk.h"

int GameObject::idCounter = 0;

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
    this->gameField = gameField;
    id = GameObject::getNextId();
}

GameObject::GameObject(GameField *gameField, int row, int column)//drugi konstruktor dla obstacle i opponent
{
//    cout<<"\tkonstruktor GameObject"<<endl<<"\t";
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
    this->gameField = gameField;
    id = GameObject::getNextId();
}

GameObject::GameObject(GameField *gameField, ifstream *inputStream) //dla wczytywanych z pliku
{
//    cout<<"\tkonstruktor GameObject"<<endl<<"\t";
    int xRelative,yRelative, row, column;
    *inputStream >> column;
    *inputStream >> row;
    *inputStream >> hp;
    initialHP = hp;
    gameField->getSquareRelativePos(row,column,&xRelative,&yRelative);
    id = GameObject::getNextId(); //dla kazdego obiektu wczytywanego z pliku nadajemy id
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
    this->gameField = gameField;
}

void GameObject::draw()
{
    if(hp <= (double)initialHP/2)
    {
        al_draw_scaled_bitmap(imageHalfHP,0,0,al_get_bitmap_width(imageHalfHP), al_get_bitmap_height(imageHalfHP),x,y,xLength,yLength,0);
    }
    else
    {
        al_draw_scaled_bitmap(image,0,0,al_get_bitmap_width(image), al_get_bitmap_height(image),x,y,xLength,yLength,0);
    }
}

bool GameObject::isItsPosition(int randomRow, int randomColumn)
{
    return randomRow == gridYPos && randomColumn == gridXPos;//obiekt posiada juz o sobie te informacje w atrybutach
}

void GameObject::displayOnConsole()
{
    cout<<"\tGameObject, pozycja: X " << gridXPos << ", Y: "<<gridYPos<< ", hp:  "<< hp<<endl;
}

GameObject::~GameObject()
{
//    cout<<"\tdestruktor GameObject"<<endl<<"\t";
}

void GameObject::saveToStream(ofstream *outputStream) //zapisujemy kod, pozycje, hp
{
    *outputStream << " " << code << " " << gridXPos << " " << gridYPos << " " << hp; //narazie kazdy obiekt ma te atrybuty
}

GameObject* GameObject::getGameObjectByCode(GameField *gameField,int code, ifstream *inputStream)
{
    switch(code)
    {
        case Obstacle::OBSTACLE_CODE:
            if(inputStream==NULL)
            {
                return new Obstacle(gameField);
            }
            else
            {
                return new Obstacle(gameField,inputStream);
            }
        case Defense::DEFENSE_CODE:
            if(inputStream==NULL)
            {
                return new Defense(gameField);
            }
            else
            {
                return new Defense(gameField,inputStream);
            }
        case DefenseIce::DEFENSE_ICE_CODE:
            if(inputStream==NULL)
            {
                return new DefenseIce(gameField);
            }
            else
            {
                return new DefenseIce(gameField,inputStream);
            }
        case DefenseWalk::DEFENSE_WALK_CODE:
            if(inputStream==NULL)
            {
                return new DefenseWalk(gameField);
            }
            else
            {
                return new DefenseWalk(gameField,inputStream);
            }
        case Opponent::OPPONENT_CODE:
            if(inputStream==NULL)
            {
                return new Opponent(gameField);
            }
            else
            {
                return new Opponent(gameField,inputStream);
            }
    }
}

int GameObject::getNextId()
{
    return ++GameObject::idCounter;
}

bool GameObject::areObjectsClashed(GameObject *first, GameObject *second) {
    if(first->id == second->id) //przypadek gdy obiekt zderzyl sie sam ze soba nie istnieje
    {
        return false;
    }
    else //rysunek pomocniczy
    {
        return ((first->x <= second->x && first->x + first->xLength > second->x) || (second->x <= first->x && second->x + second->xLength > first->x))
               && ((first->y <= second->y && first->y+first->yLength > second->y)||(second->y <= first->y && second->y+second->yLength > first->y));
    }
}

bool GameObject::willDie()
{
    return hp<=0;
}

void GameObject::resetIdCounter()
{
    GameObject::idCounter=0;
}

bool GameObject::isOutsideField()
{
    return x < gameField->x || x+xLength > gameField->x+gameField->xLength; //rysunek pomocniczy
}















