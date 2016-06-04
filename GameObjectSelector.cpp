#include "GameObjectSelector.h"
#include "Defense.h"
#include "Obstacle.h"
#include "DefenseIce.h"
#include "DefenseWalk.h"

GameObjectSelector::GameObjectSelector(int x, int y, int xLength, int yLength, int code) {
    cout<<"\tkonstruktor GameObjectSelector"<<endl;
    this->x = x;
    this->y = y;
    this->xLength = xLength;
    this->yLength = yLength;
    this->code = code;
    allegroColor = al_map_rgb( 246,  71, 71);
    string imageName,imageDisabledName;
    switch (code){
        case GAME_OBJECT_SELECTOR_CODE_DEFENSE :
            imageName = "bitmaps/defense_buy.png";
            imageDisabledName = "bitmaps/defense_buy_disabled.png";
            price = 150;
            gameObjectCode = Defense::DEFENSE_CODE;
            break;
        case GAME_OBJECT_SELECTOR_CODE_DEFENSE_ICE :
            imageName = "bitmaps/defense_ice_buy.png";
            imageDisabledName = "bitmaps/defense_ice_buy_disabled.png";
            price = 200;
            gameObjectCode = DefenseIce::DEFENSE_ICE_CODE;
            break;
        case GAME_OBJECT_SELECTOR_CODE_DEFENSE_WALK :
            imageName = "bitmaps/defense_walk_buy.png";
            imageDisabledName = "bitmaps/defense_walk_buy_disabled.png";
            price = 300;
            gameObjectCode = DefenseWalk::DEFENSE_WALK_CODE;
            break;
        case GAME_OBJECT_SELECTOR_CODE_OBSTACLE :
            imageName = "bitmaps/obstacle_buy.png";
            imageDisabledName = "bitmaps/obstacle_buy_disabled.png";
            price = 100;
            gameObjectCode = Obstacle::OBSTACLE_CODE;
            break;
    }
    image = al_load_bitmap(imageName.c_str());
    imageDisabled = al_load_bitmap(imageDisabledName.c_str());
}

void GameObjectSelector::draw()
{
    switch (state){
        case STATE_CODE_CLICKED:
            al_draw_rectangle(x, y, x+xLength, y+yLength,allegroColor,5);
        case STATE_CODE_NORMAL:
            al_draw_scaled_bitmap(image,0,0,al_get_bitmap_width(image), al_get_bitmap_height(image),x,y,xLength,yLength,0);
            break;
        case STATE_CODE_DISABLED:
            al_draw_scaled_bitmap(imageDisabled,0,0,al_get_bitmap_width(imageDisabled), al_get_bitmap_height(imageDisabled),x,y,xLength,yLength,0);
            break;
    }
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



