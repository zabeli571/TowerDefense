#include "Play.h"
#include "Game.h"
#include "Bullet.h"
#include "Opponent.h"

Play::Play(Game *game,vector<GameObject *> *gameObjects, Statistics *statistics)
{
    cout<<"konstruktor Play"<<endl;
    this->game = game;
    this->gameObjects = gameObjects;
    this->statistics = statistics;
    GameObject::resetIdCounter(); //ustawiam na 0
}

Play::~Play()
{
    cout<<"destruktor Play"<<endl;
}

int Play::run()
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
        al_init_timeout(&timeout, ((double)REFRESH_TIME)/((double)1000)); //refresh_time=50ms
        al_wait_for_event_until(event_queue, &ev,&timeout);//funkcja zatrzymuje dzialanie programu do czasu eventu myszy lub miniecia timeoutu
        eventTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()); //zapisywanie czasu od 1970
        if(eventTime.count() - lastEventTime.count() >= REFRESH_TIME) //aby nie wykonywalo sie co chwile przy ruchu myszy, funkcja wykonuje sie przynajmniej co 50ms
        {
            lastEventTime = eventTime;
            for(int i=0;i<gameObjects->size();i++) //2 fory, iteruje sie po wszystkich obiektach,by sprawdzic czy doszlo do zderzenia
            {
                for(int j=0;j<gameObjects->size();j++)
                {
                    if(GameObject::areObjectsClashed((*gameObjects)[i], (*gameObjects)[j])) //sprawdzam czy obiekt i zderzyl sie z j
                    {
                        //aby sprawdzic co jest czym
                        (*gameObjects)[i]->collisionWith((*gameObjects)[j]);// funkcja wirtualna GameObject, poznam typ i, bo wywola sie dla odpowiedniej klasy
                    }
                }
                if((*gameObjects)[i]->willDie()) //sprawdzam czy hp <= 0
                {
                    if((*gameObjects)[i]->getCode() == Opponent::OPPONENT_CODE)
                    {
                        statistics->addOpponentDefeated(); //dodajemy do statystyk pokonanego przeciwnika
                    }
                    deleteObject((*gameObjects)[i]); //hp <= 0 usuwamy
                }
                else
                {
                    (*gameObjects)[i]->move();
                    (*gameObjects)[i]->doAction(this); //tylko defense wykonuje akcje - zawsze strzela, niezaleznie od kolizji
                }
            }
            if(checkForWin())//zwroci true jesli nie ma przeciwnikow
            {
                return Play::VICTORY_CODE;
            }
            if(checkForOutsideField()) //zwroci true gdy opponent przekroczy gamefield
            {
                return Play::DEFEAT_CODE;
            }
        }
        game->redraw(); //przerysowujemy, play i game sa friendami
    }
}

void Play:: deleteObject(GameObject *gameObject)
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

void Play::addObject(GameObject *gameObject)
{
    gameObjects->push_back(gameObject);
}

bool Play::checkForOutsideField()//przegrywam gdy opoonent przekroczy pole gry, gdy pocisk przekroczy pole gry zostaje usuniety
{
    for(int i=0;i<gameObjects->size();i++)
    {
        if((*gameObjects)[i]->isOutsideField())
        {
            if((*gameObjects)[i]->getCode() == Opponent::OPPONENT_CODE) //gdy opponent przekroczy pole
            {
                return true;
            }
            else
            {
                deleteObject((*gameObjects)[i]); //usuwamy gdy to nie opponent
            }
        }
    }
    return false;
}

bool Play::checkForWin()
{
    for(int i=0;i<gameObjects->size();i++)
    {
        if((*gameObjects)[i]->getCode() == Opponent::OPPONENT_CODE)//sprawdzam czy na planszy sa jeszcze przeciwnicy
        {
            return false;
        }
    }
    return true;
}



