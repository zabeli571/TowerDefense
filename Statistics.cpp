#include "Statistics.h"
#include "Play.h"
#include "Defense.h"
#include "Obstacle.h"

Statistics::Statistics()
{
    x = 300;
    y = 100;
    xLength = 430;
    yLength = 430;

    backButton = new Button(x+xLength/2 - 100, y+yLength-70 ,200, 50, Button::BUTTON_PLAY_START , "POWROT");

    fontSize=40;
    font=al_load_ttf_font("fonts/font3.ttf",fontSize,0);

    points = 0;
    opponentsDefeated = 0;
    obstaclesStand = 0;
    defensesStand = 0;
    cout<<"\tkonstruktor Statistics"<<endl;
}

Statistics::~Statistics()
{
    cout<<"\tdestruktor Statistics"<<endl;
}

void Statistics::draw()
{
    al_draw_scaled_bitmap(image,0,0,al_get_bitmap_width(image), al_get_bitmap_height(image),x,y,xLength,yLength,0);
    al_draw_text(font, al_map_rgba(255,  229, 204,128),x+xLength/2 +50,y+yLength/2-fontSize/2-85,ALLEGRO_ALIGN_LEFT,createPointsString(opponentsDefeated,POINTS_PER_OPPONENT).c_str());
    al_draw_text(font, al_map_rgba(255,  229, 204,128),x+xLength/2 +50,y+yLength/2-fontSize/2-35,ALLEGRO_ALIGN_LEFT,createPointsString(defensesStand,POINTS_PER_DEFENSE).c_str());
    al_draw_text(font, al_map_rgba(255,  229, 204,128),x+xLength/2 +50,y+yLength/2-fontSize/2+15,ALLEGRO_ALIGN_LEFT,createPointsString(obstaclesStand,POINTS_PER_OBSTACLE).c_str());

    char *chr = new char;
    sprintf(chr, "%d", sumPoints());
    al_draw_text(font, al_map_rgba(255,  229, 204,128),x+xLength/2 +50,y+yLength/2-fontSize/2+75,ALLEGRO_ALIGN_LEFT,chr);

    backButton->draw();
    al_flip_display();
}

void Statistics::setPlayFinished(int code)
{
    if(code == Play::VICTORY_CODE)
    {
        points +=10;
        image = al_load_bitmap("layouts/winner.png");
    }
    else
    {
        points -=10;
        image = al_load_bitmap("layouts/looser.png");
    }
}

void Statistics::addOpponentDefeated()
{
    opponentsDefeated++;
}

void Statistics::countDefendersStand(vector<GameObject*> *gameObjects)
{
    for(int i =0; i< gameObjects->size();i++)
    {
        if((*gameObjects)[i]->getCode() == Defense::DEFENSE_CODE)
        {
            defensesStand++;
        }
        else if((*gameObjects)[i]->getCode() == Obstacle::OBSTACLE_CODE)
        {
            obstaclesStand++;
        }
    }
}

int Statistics::sumPoints()
{
    return points + opponentsDefeated*POINTS_PER_OPPONENT + obstaclesStand*POINTS_PER_OBSTACLE + defensesStand*POINTS_PER_DEFENSE;
}

string Statistics::createPointsString(int item, int pointsPerItem)
{
    char *chr = new char;
    sprintf(chr, "%d", item);
    string str(chr); //tworze stringa z char*
    str = str + " x ";
    sprintf(chr, "%d", pointsPerItem);
    str = str + chr;
    return str;
}

int Statistics::getButtonCodeWhenClicked() {
    ALLEGRO_MOUSE_STATE state;
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_mouse_event_source());
    while(true)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);//czekam na klikniecie
        al_get_mouse_state(&state);
        if (state.buttons & 1)//spr czy klikniety
        {
            if(backButton->getCodeIfClicked(state.x,state.y,NULL)){
                return BACK_CODE;
            }
        }
    }
}

















