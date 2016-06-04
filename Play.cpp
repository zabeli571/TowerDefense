#include "Play.h"
#include "Game.h"
#include "Bullet.h"
#include "Opponent.h"
#include "Text.h"
#include "NumberField.h"
#include "ProgressField.h"

Play::Play(string mapName, Game *game,vector<GameObject *> *gameObjects, vector<MainObject*> *interfaceObjects, Statistics *statistics)
{
    cout<<"konstruktor Play"<<endl;
    this->game = game;
    this->gameObjects = gameObjects;
    this->interfaceObjects = interfaceObjects;
    this->statistics = statistics;
    GameObject::resetIdCounter(); //ustawiam na 0
    loadObjects(mapName);
}

Play::~Play()
{
    cout<<"destruktor Play"<<endl;
}

int Play::run()
{
    drawPlay();
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
        al_get_mouse_state(&state);
        if (state.buttons & 1)//spr czy klikniety
        {
            manageMouseClicked(&state);
        }
        eventTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()); //zapisywanie czasu od 1970
        manageWaveReady(eventTime.count());
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
                game->deleteObjects();
                return Play::VICTORY_CODE;
            }
            if(checkForOutsideField()) //zwroci true gdy opponent przekroczy gamefield
            {
                game->deleteObjects();
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

bool Play::checkForOutsideField()//przegrywam gdy opponent przekroczy pole gry, gdy pocisk przekroczy pole gry zostaje usuniety
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


void Play::loadObjects(string mapName)
{
    ifstream inputStream(mapName);
    int objectsCount;
    inputStream >> money;
    inputStream >> waves;
    inputStream >> frequency;
    inputStream >> objectsCount; //pobieramy liczbe obiektow
    for(int i=0;i<objectsCount;i++)
    {
        int code;
        inputStream >> code;
        GameObject *gameObject = GameObject::getGameObjectByCode(&gameField,code,&inputStream);
        gameObjects->push_back(gameObject); //stworzony w getGameObjectByCode nowy obiekt dodajemy do wektora

    }
    inputStream.close();
}

void Play::drawPlay()
{
    interfaceObjects->push_back(new Button(910, 20 ,80,50, Button::BUTTON_PLAY_MENU , "MENU")); //dodaje przycisk MENU
    interfaceObjects->push_back(&gameField); //dodaje gamefield
    interfaceObjects->push_back(new Text(100,470,30,"Liczba monet",ALLEGRO_ALIGN_LEFT));
    interfaceObjects->push_back(new NumberField(250,470,30,&money));
    interfaceObjects->push_back(new Text(450,470,30,"Zostalo fal",ALLEGRO_ALIGN_LEFT));
    interfaceObjects->push_back(new NumberField(570,470,30,&waves));
    interfaceObjects->push_back(new Text(700,470,30,"Czestotliwosc fal",ALLEGRO_ALIGN_LEFT));
    interfaceObjects->push_back(new NumberField(850,470,30,&frequency));
    interfaceObjects->push_back(new Text(450,545,30,"Czas do nastepnej fali przeciwnikow",ALLEGRO_ALIGN_LEFT));

    interfaceObjects->push_back(&progressField);
}

void Play::manageMouseClicked(ALLEGRO_MOUSE_STATE *state) {
    int code;
    if(getCodeIfClicked(state, &code))
    {
        switch (code){
            case Button::BUTTON_PLAY_MENU:
                cout<<"MENU!";
                break;
        }
    }
}

bool Play::getCodeIfClicked(ALLEGRO_MOUSE_STATE *state, int *codePointer) {
    for(int i=0;i<gameObjects->size();i++)
    {
        int code=(*gameObjects)[i]->getCodeIfClicked(state->x,state->y, &clickedObject);
        if(code != 0)
        {
            *codePointer = code;
            return true;
        }
    }
    for(int i=0; i<interfaceObjects->size();i++)
    {
        int code=(*interfaceObjects)[i]->getCodeIfClicked(state->x,state->y, &clickedObject);
        if(code != 0)
        {
            *codePointer = code;
            return true;
        }
    }
    return false;
}

void Play::manageWaveReady(long long int currentTime) {
    if(waves > 0)
    {
        if(currentTime - lastWaveTime > (frequency*1000))
        {
            progressField.setProgress(100);
            lastWaveTime = currentTime;
            waves--;
            createWave();
        } else
        {
            int progress = ((double)(currentTime-lastWaveTime)/(frequency*1000)*100);
            progressField.setProgress(progress);
        }
    }
}

void Play::createWave() {
    for(int i=1;i<=5;i++)
    {
        gameObjects->push_back(new Opponent(&gameField,i,10));
    }
}



