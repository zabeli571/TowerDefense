#include "GameField.h"

using namespace std;

GameField:: GameField()
{
    cout<<"\tkonstruktor GameField"<<endl;
    allegroColor=al_map_rgb( 0,  102, 102);
    x=GAME_FIELD_XPOS;
    y=GAME_FIELD_YPOS;
    xLength=GAME_FIELD_WIDTH;
    yLength=GAME_FIELD_HEIGHT;
    code=GAME_FIELD_CODE;
    srand(time(NULL));
}

void GameField::draw()
{
    al_draw_filled_rectangle(x, y, x+xLength, y+yLength, allegroColor);
    for(int i=0;i<6;i++)
    {
        al_draw_line(x, y +i*GAME_FIELD_SQUARE, x + xLength, y +i*GAME_FIELD_SQUARE , al_map_rgb(255,  229, 204), 2);
    }
    for(int i=0;i<11;i++)
    {
        al_draw_line(x +i*GAME_FIELD_SQUARE, y, x  +i*GAME_FIELD_SQUARE, y + yLength , al_map_rgb(255,  229, 204), 2);
    }
}

void GameField::whichSquare(int *x, int *y, int *row, int *column)//ktory zostal klikniety
{
    int xx=0;
    int yy=0;
    int r=0;
    int c=0;
    for(int i=1;i<6;i++)
    {
        if(clickYPos<this->y+i*GAME_FIELD_SQUARE)
        {
            yy=(i-1)*GAME_FIELD_SQUARE;
            r=i;
            break;
        }
    }
    for(int i=1;i<11;i++)
    {
        if(clickXPos<this->x+i*GAME_FIELD_SQUARE)
        {
            xx=(i-1)*GAME_FIELD_SQUARE;
            c=i;
            break;
        }
    }
    *y=yy;
    *x=xx;
    *row=r;
    *column=c;
}

void GameField::changeStateToActive()
{
    allegroColor=al_map_rgb( 255,  153, 153);//rozowy

}

void GameField::changeStateToInactive()
{
    allegroColor=al_map_rgb( 0,  102, 102);//niebieski
}

void GameField::getProperties(int *x, int *y, int *sq)//gamefield xpos, ypos,szerokosc kwadratu
{
    *x=this->x;//x=GAME_FIELD_XPOS
    *y=this->y;//y=GAME_FIELD_YPOS
    *sq=GAME_FIELD_SQUARE;
}

GameField::~GameField()
{
    cout << "destruktor GameField"<< endl;
}

void GameField::getRandomSquare(int *row, int *column)//losuje kwadracik
{
    *row = (rand() % GAME_FIELD_ROWS)+1;
    *column = (rand() % GAME_FIELD_COLUMNS) +1;
    cout << "wylosowano "<< *column << ", "<< *row << endl;
}

void GameField::getSquareRelativePos(int row, int column, int *xRelativePos, int *yRelativePos)//wzgledem okna gry
{
    *yRelativePos=(row-1)*GAME_FIELD_SQUARE;
    *xRelativePos=(column-1)*GAME_FIELD_SQUARE;
}

int GameField::getSquareCount()//wielkosc pola - 50 kwadracikow
{
    return GAME_FIELD_COLUMNS*GAME_FIELD_ROWS;
}