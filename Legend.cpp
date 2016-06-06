#include "Legend.h"

Legend::Legend()
{
    cout<<"\tkonstruktor Legend"<<endl;
    x = 160;
    y = 60;
    xLength = 667;
    yLength = 502;

    backButton = new Button(x+xLength/2 + 50, y+yLength-90 ,200, 50, BACK_CODE , "POWROT");
    image = al_load_bitmap("layouts/legend.png");
}

Legend::~Legend()
{
    cout<<"\tdestruktor Legend"<<endl;
}

void Legend::draw()
{
    al_draw_scaled_bitmap(image,0,0,al_get_bitmap_width(image), al_get_bitmap_height(image),x,y,xLength,yLength,0);
    backButton->draw();
    al_flip_display();
}

int Legend::getButtonCodeWhenClicked()
{
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
            if(backButton->getCodeIfClicked(state.x,state.y,NULL))
            {
                return BACK_CODE;
            }
        }
    }
}







