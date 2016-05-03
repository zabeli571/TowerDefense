#include "GameField.h"

using namespace std;

GameField::GameField(int code) {
    cout<<"\tkonstruktor GameField"<<endl;
    switch (code){
        case GAME_FIELD_CREATOR_CODE :
            allegroColor=al_map_rgb( 0,  102, 102);
            x=CREATOR_XPOS;
            y=CREATOR_YPOS;
            xLength=CREATOR_WIDTH;
            yLength=CREATOR_HEIGHT;
            this->code=GAME_FIELD_CREATOR_CODE;
            rows = CREATOR_ROWS;
            columns = CREATOR_COLUMNS;
            break;
        case GAME_FIELD_PLAY_CODE :
            allegroColor=al_map_rgb( 0,  102, 102);
            x=PLAY_XPOS;
            y=PLAY_YPOS;
            xLength=PLAY_WIDTH;
            yLength=PLAY_HEIGHT;
            this->code=GAME_FIELD_PLAY_CODE;
            rows = PLAY_ROWS;
            columns = PLAY_COLUMNS;
            break;
        default:
            cout << "Nieznany kod GameField";
            break;
    }
    srand(time(NULL));
}

void GameField::draw()
{
    al_draw_filled_rectangle(x, y, x+xLength, y+yLength, allegroColor);
    for(int i=0;i<6;i++)
    {
        al_draw_line(x, y +i*getSquareSize(), x + xLength, y +i*getSquareSize() , al_map_rgb(255,  229, 204), 2);
    }
    for(int i=0;i<11;i++)
    {
        al_draw_line(x +i*getSquareSize(), y, x  +i*getSquareSize(), y + yLength , al_map_rgb(255,  229, 204), 2);
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
        if(clickYPos<this->y+i*getSquareSize())
        {
            yy=(i-1)*getSquareSize();
            r=i;
            break;
        }
    }
    for(int i=1;i<11;i++)
    {
        if(clickXPos<this->x+i*getSquareSize())
        {
            xx=(i-1)*getSquareSize();
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
    *sq=getSquareSize();
}

GameField::~GameField()
{
    cout << "destruktor GameField"<< endl;
}

void GameField::getRandomSquare(int *row, int *column)//losuje kwadracik
{
    *row = (rand() % rows)+1;
    *column = (rand() % columns) +1;
    cout << "wylosowano "<< *column << ", "<< *row << endl;
}

void GameField::getSquareRelativePos(int row, int column, int *xRelativePos, int *yRelativePos)//wzgledem okna gry
{
    *yRelativePos=(row-1)*getSquareSize();
    *xRelativePos=(column-1)*getSquareSize();
}

int GameField::getSquareCount()//wielkosc pola - 50 kwadracikow
{
    return rows*columns;
}

int GameField::getSquareSize() {
    return xLength/columns;
}