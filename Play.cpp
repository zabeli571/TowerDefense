#include "Play.h"
#include "Game.h"

Play::Play(Game *game,vector<GameObject *> *gameObjects) {
    cout<<"konstruktor Play"<<endl;
    this->game = game;
    this->gameObjects = gameObjects;
    GameObject::resetIdCounter();
}

Play::~Play()
{
    cout<<"destruktor Play"<<endl;
}

void Play::run()
{
    ALLEGRO_MOUSE_STATE state;
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_mouse_event_source());

    std::chrono::milliseconds lastEventTime = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
    std::chrono::milliseconds eventTime;

    while(true)
    {
        ALLEGRO_EVENT ev;
        ALLEGRO_TIMEOUT timeout;
        al_init_timeout(&timeout, ((double)REFRESH_TIME)/((double)1000));
        al_wait_for_event_until(event_queue, &ev,&timeout);//czekam na event myszy lub wypuszcam po timeoucie
        eventTime = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
        if(eventTime.count() - lastEventTime.count() >= REFRESH_TIME) //aby nie przyspieszalo przy ruchu myszy
        {
            for(int i=0;i<gameObjects->size();i++)
            {
                for(int j=0;j<gameObjects->size();j++)
                {
                    if(GameObject::areObjectsClashed((*gameObjects)[i], (*gameObjects)[j])){
                        (*gameObjects)[i]->collisionWith((*gameObjects)[j]);
                    }
                }
                if((*gameObjects)[i]->willDie())
                {
                    deleteDyingObject((*gameObjects)[i]);
                }
                else
                {
                    (*gameObjects)[i]->move();
                    (*gameObjects)[i]->doAction();
                }
            }
            lastEventTime = eventTime;
        }
        game->redraw();
    }
}

void Play:: deleteDyingObject(GameObject *gameObject)
{
    int i=0;
    for(i=0; i < gameObjects->size(); i++)
    {
        if((*gameObjects)[i]==gameObject)
            break;
    }
    delete((*gameObjects)[i]);
    (*gameObjects).erase((*gameObjects).begin()+i);
}





