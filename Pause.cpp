#include "Pause.h"
Pause::Pause()
{
    cout<<"\tkonstruktor Pause"<<endl;
    x = 300;
    y = 100;
    xLength = 430;
    yLength = 430;
    buttons.push_back(new Button(x+xLength/2 - 100, y+100 ,200, 50, BACK_CODE , "WROC DO GRY"));
    buttons.push_back(new Button(x+xLength/2 - 100, y+200 ,200, 50, SAVE_CODE , "ZAPISZ GRE"));
    buttons.push_back(new Button(x+xLength/2 - 100, y+300 ,200, 50, EXIT_CODE , "WYJDZ Z GRY"));
    allegroColor = al_map_rgb(153,204,255);
}

void Pause::draw()
{
    al_draw_rectangle(x, y, x+xLength, y+yLength,al_map_rgb( 0,  102, 102),10);
    al_draw_filled_rectangle(x, y, x+xLength, y+yLength,allegroColor);
    for(list<Button*>::iterator iter = buttons.begin(); iter != buttons.end() ; iter++)
    {
        (*iter)->draw();
    }
    al_flip_display();
}


Pause::~Pause()
{
    cout<<"\tdestruktor Pause"<<endl;
}

int Pause::getButtonCodeWhenClicked()
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
            for(list<Button*>::iterator iter = buttons.begin(); iter != buttons.end() ; iter++)
            {
                int code=(*iter)->getCodeIfClicked(state.x,state.y, NULL);
                if(code != 0)
                {
                    return code;
                }
            }
        }
    }
}