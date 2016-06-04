#include "GameObjectSelector.h"
#include "Defense.h"
#include "Obstacle.h"

GameObjectSelector::GameObjectSelector(int x, int y, int xLength, int yLength, int code) {
    cout<<"\tkonstruktor GameObjectSelector"<<endl;
    this->x = x;
    this->y = y;
    this->xLength = xLength;
    this->yLength = yLength;
    this->code = code;
    allegroColor = al_map_rgb( 246,  71, 71);
    string imageName;
    switch (code){
        case GAME_OBJECT_SELECTOR_CODE_DEFENSE :
            imageName = "bitmaps/defense.png";
            price = 150;
            gameObjectCode = Defense::DEFENSE_CODE;
            break;
        case GAME_OBJECT_SELECTOR_CODE_OBSTACLE :
            imageName = "bitmaps/obstacle.png";
            price = 100;
            gameObjectCode = Obstacle::OBSTACLE_CODE;
            break;
    }
    image = al_load_bitmap(imageName.c_str());
}

void GameObjectSelector::draw()
{
    if(state == STATE_CODE_CLICKED)
    {
        al_draw_rectangle(x, y, x+xLength, y+yLength,allegroColor,5);
    }
    else if(state == STATE_CODE_DISABLED)
    {
        al_draw_rectangle(x+xLength/2, y+yLength/2, x+xLength, y+yLength/2,allegroColor,5);
    }
    al_draw_scaled_bitmap(image,0,0,al_get_bitmap_width(image), al_get_bitmap_height(image),x,y,xLength,yLength,0);
}

GameObjectSelector:: ~GameObjectSelector()
{
    cout<<"\tdestruktor GameObjectSelector"<<endl<<"\t";
}

int GameObjectSelector::getPrice() {
    return price;
}

int GameObjectSelector::getGameObjectCode() {
    return gameObjectCode;
}



