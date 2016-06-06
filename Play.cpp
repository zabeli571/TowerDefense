#include "Play.h"
#include "Game.h"
#include "Bullet.h"
#include "Opponent.h"
#include "Text.h"
#include "NumberField.h"
#include "ProgressField.h"
#include "GameObjectSelector.h"
#include "Defense.h"
#include "Obstacle.h"
#include "OpponentShoot.h"
#include "OpponentFly.h"
#include "Pause.h"
#include <list>

Play::Play(string mapName, Game *game,list<GameObject *> *gameObjects, list<MainObject*> *interfaceObjects, Statistics *statistics)
{
    cout<<"konstruktor Play"<<endl;
    this->game = game;
    this->gameObjects = gameObjects;
    this->interfaceObjects = interfaceObjects;
    this->statistics = statistics;
    GameObject::resetIdCounter(); //ustawiam na 0
    gameField = new GameField(GameField::GAME_FIELD_PLAY_CODE);
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
            if(manageMouseClicked(&state) == Pause::EXIT_CODE)
            {
                return Pause::EXIT_CODE;
            }
        }
        eventTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()); //zapisywanie czasu od 1970
        manageWaveReady(eventTime.count());
        manageGameObjectSelectorsState();
        if(eventTime.count() - lastEventTime.count() >= REFRESH_TIME) //aby nie wykonywalo sie co chwile przy ruchu myszy, funkcja wykonuje sie przynajmniej co 50ms
        {
            lastEventTime = eventTime;
            for(list<GameObject*>::reverse_iterator iter1 = gameObjects->rbegin(); iter1 != gameObjects->rend() ; iter1++)//2 fory, iteruje sie po wszystkich obiektach,by sprawdzic czy doszlo do zderzenia
            {
                for(list<GameObject*>::iterator iter2 = gameObjects->begin(); iter2 != gameObjects->end() ; iter2++)
                {
                    if(GameObject::areObjectsClashed((*iter1), (*iter2))) //sprawdzam czy obiekt i zderzyl sie z j
                    {
                        //aby sprawdzic co jest czym
                        (*iter1)->collisionWith(*iter2);// funkcja wirtualna GameObject, poznam typ i, bo wywola sie dla odpowiedniej klasy
                    }
                }
                if((*iter1)->willDie()) //sprawdzam czy hp <= 0
                {
                    if((*iter1)->getCode() == Opponent::OPPONENT_CODE || (*iter1)->getCode() == OpponentFly::OPPONENT_FLY_CODE ||(*iter1)->getCode() == OpponentShoot::OPPONENT_SHOOT_CODE)
                    {
                        increaseMoneyForDefeatingOpponent((*iter1)->getCode());
                        statistics->addOpponentDefeated(); //dodajemy do statystyk pokonanego przeciwnika
                    }
                    game->deleteObject(*iter1); //hp <= 0 usuwamy
                }
                else
                {
                    (*iter1)->move();
                    (*iter1)->doAction(this); //tylko defense wykonuje akcje - zawsze strzela, niezaleznie od kolizji
                }
            }
            if(checkForWin())//zwroci true jesli nie ma przeciwnikow
            {
                statistics->countDefendersStand(gameObjects); //licze chomiki i przeszkody, ktore pozostaly
                game->deleteObjects();
                return Play::VICTORY_CODE;
            }
            if(checkForOutsideField()) //zwroci true gdy opponent przekroczy gamefield
            {
                statistics->countDefendersStand(gameObjects); //licze chomiki i przeszkody, ktore pozostaly
                game->deleteObjects();
                return Play::DEFEAT_CODE;
            }
        }
        game->redraw(); //przerysowujemy, play i game sa friendami
    }
}

void Play::addObject(GameObject *gameObject)
{
    gameObjects->push_back(gameObject);
}

bool Play::checkForOutsideField()//przegrywam gdy opponent przekroczy pole gry, gdy pocisk przekroczy pole gry zostaje usuniety
{
    for(list<GameObject*>::reverse_iterator iter = gameObjects->rbegin(); iter != gameObjects->rend() ; iter++)
    {
        if((*iter)->isOutsideField())
        {
            if((*iter)->getCode() == Opponent::OPPONENT_CODE || (*iter)->getCode() == OpponentFly::OPPONENT_FLY_CODE ||(*iter)->getCode() == OpponentShoot::OPPONENT_SHOOT_CODE) //gdy opponent przekroczy pole
            {
                return true;
            }
            else
            {
                game->deleteObject((*iter)); //usuwamy gdy to nie opponent
            }
        }
    }
    return false;
}

bool Play::checkForWin()
{
    if(waves == 0)
    {
        for(list<GameObject*>::iterator iter = gameObjects->begin(); iter != gameObjects->end() ; iter++)
        {
            if ((*iter)->getCode() == Opponent::OPPONENT_CODE || (*iter)->getCode() == OpponentFly::OPPONENT_FLY_CODE ||(*iter)->getCode() == OpponentShoot::OPPONENT_SHOOT_CODE)//sprawdzam czy na planszy sa jeszcze przeciwnicy
            {
                return false;
            }
        }
        return true;
    }
    return false;
}


void Play::loadObjects(string mapName)
{
    ifstream inputStream(mapName);
    int objectsCount;
    inputStream >> money;
    inputStream >> waves;
    initialWaves = waves;
    inputStream >> frequency;
    inputStream >> objectsCount; //pobieramy liczbe obiektow
    for(int i=0;i<objectsCount;i++)
    {
        int code;
        inputStream >> code;
        GameObject *gameObject = GameObject::getGameObjectByCode(gameField,code,&inputStream);
        gameObjects->push_back(gameObject); //stworzony w getGameObjectByCode nowy obiekt dodajemy do wektora

    }
    inputStream.close();
}

void Play::drawPlay()
{
    interfaceObjects->push_back(new Button(910, 20 ,80,50, Button::BUTTON_PLAY_MENU , "MENU")); //dodaje przycisk MENU
    interfaceObjects->push_back(gameField); //dodaje gamefield
    interfaceObjects->push_back(new Text(100,470,30,"Liczba monet",ALLEGRO_ALIGN_LEFT));
    interfaceObjects->push_back(new NumberField(250,470,30,&money));
    interfaceObjects->push_back(new Text(450,470,30,"Zostalo fal",ALLEGRO_ALIGN_LEFT));
    interfaceObjects->push_back(new NumberField(570,470,30,&waves));
    interfaceObjects->push_back(new Text(700,470,30,"Czestotliwosc fal",ALLEGRO_ALIGN_LEFT));
    interfaceObjects->push_back(new NumberField(850,470,30,&frequency));
    interfaceObjects->push_back(new Text(450,545,30,"Czas do nastepnej fali przeciwnikow",ALLEGRO_ALIGN_LEFT));

    GameObjectSelector *gameObjectSelector = new GameObjectSelector(10,50,80,80,GameObjectSelector::GAME_OBJECT_SELECTOR_CODE_DEFENSE);
    gameObjectsSelectors.push_back(gameObjectSelector);
    interfaceObjects->push_back(gameObjectSelector);
    gameObjectSelector = new GameObjectSelector(10,150,80,80,GameObjectSelector::GAME_OBJECT_SELECTOR_CODE_DEFENSE_ICE);
    gameObjectsSelectors.push_back(gameObjectSelector);
    interfaceObjects->push_back(gameObjectSelector);
    gameObjectSelector = new GameObjectSelector(10,250,80,80,GameObjectSelector::GAME_OBJECT_SELECTOR_CODE_DEFENSE_WALK);
    gameObjectsSelectors.push_back(gameObjectSelector);
    interfaceObjects->push_back(gameObjectSelector);
    gameObjectSelector = new GameObjectSelector(10,350,80,80,GameObjectSelector::GAME_OBJECT_SELECTOR_CODE_OBSTACLE);
    gameObjectsSelectors.push_back(gameObjectSelector);
    interfaceObjects->push_back(gameObjectSelector);

    progressField =new ProgressField(750,550,150,30);
    interfaceObjects->push_back(progressField);
}

int Play::manageMouseClicked(ALLEGRO_MOUSE_STATE *state)
{
    int code;
    if(getCodeIfClicked(state, &code))
    {
        switch (code){
            case GameObjectSelector::GAME_OBJECT_SELECTOR_CODE_DEFENSE:
            case GameObjectSelector::GAME_OBJECT_SELECTOR_CODE_DEFENSE_ICE:
            case GameObjectSelector::GAME_OBJECT_SELECTOR_CODE_DEFENSE_WALK:
            case GameObjectSelector::GAME_OBJECT_SELECTOR_CODE_OBSTACLE:
                {
                    GameObjectSelector* gameObjectSelector = getSelectorByClicked();
                    if(gameObjectSelector->getState() == MainObject::STATE_CODE_NORMAL)
                    {
                        gameObjectSelector->setState(MainObject::STATE_CODE_CLICKED);
                        addGameObjectCode = gameObjectSelector->getGameObjectCode();
                    }
                }
                break;
            case GameField::GAME_FIELD_PLAY_CODE:
                if(addGameObjectCode!=0)
                {
                    money -= getSelectorByCode()->getPrice();
                    gameObjects->push_back(GameObject::getGameObjectByCode(gameField,addGameObjectCode,NULL));
                    addGameObjectCode = 0;
                }
                break;
            case Button::BUTTON_PLAY_MENU:
                std::chrono::milliseconds pauseStartTime = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
                for(list<GameObject*>::iterator iter = gameObjects->begin(); iter != gameObjects->end() ; iter++)
                {
                    (*iter)->managePauseStart(pauseStartTime);
                }
                Pause pause;
                pause.draw();
                int code = pause.getButtonCodeWhenClicked();
                if(code == Pause::EXIT_CODE)
                {
                    return code;
                }
                else
                {
                    if(code == Pause::SAVE_CODE)
                    {

                    }
                    std::chrono::milliseconds pauseEndTime = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
                    for(list<GameObject*>::iterator iter = gameObjects->begin(); iter != gameObjects->end() ; iter++)
                    {
                        (*iter)->managePauseEnd(pauseEndTime);
                    }
                }
        }
    }
    return 0;
}

bool Play::getCodeIfClicked(ALLEGRO_MOUSE_STATE *state, int *codePointer)
{
    for(list<GameObject*>::iterator iter = gameObjects->begin(); iter != gameObjects->end() ; iter++)
    {
        int code=(*iter)->getCodeIfClicked(state->x,state->y, &clickedObject);
        if(code != 0)
        {
            *codePointer = code;
            return true;
        }
    }
    for(list<MainObject*>::iterator iter = interfaceObjects->begin(); iter != interfaceObjects->end() ; iter++)
    {
        int code=(*iter)->getCodeIfClicked(state->x,state->y, &clickedObject);
        if(code != 0)
        {
            *codePointer = code;
            return true;
        }
    }
    return false;
}

void Play::manageWaveReady(long long int currentTime)
{
    if(waves > 0)
    {
        if(currentTime - lastWaveTime > (frequency*1000) || initialWaves == waves)
        {
            progressField->setProgress(100);
            lastWaveTime = currentTime;
            waves--;
            createWave();
        } else
        {
            int progress = ((double)(currentTime-lastWaveTime)/(frequency*1000)*100);
            progressField->setProgress(progress);
        }
    }
}

void Play::createWave()
{
    srand(time(NULL));
    int shootLine = (rand() % 5)+1;
    int flyLine = shootLine;
    while(flyLine == shootLine)
    {
        flyLine = (rand() % 5)+1;
    }
    for(int i=1;i<=5;i++)
    {
        if(i == flyLine)
        {
            gameObjects->push_back(new OpponentFly(gameField,i,10));
        }
        else if(i == shootLine)
        {
            gameObjects->push_back(new OpponentShoot(gameField,i,10));
        }
        else
        {
            gameObjects->push_back(new Opponent(gameField,i,10));
        }
    }
}

void Play::manageGameObjectSelectorsState()
{
    for(list<GameObjectSelector*>::iterator iter = gameObjectsSelectors.begin(); iter != gameObjectsSelectors.end() ; iter++)
    {
        if(money < (*iter)->getPrice())
        {
            (*iter)->setState(MainObject::STATE_CODE_DISABLED);
        }
        else
        {
            if((*iter)->getGameObjectCode() != addGameObjectCode)
            {
                (*iter)->setState(MainObject::STATE_CODE_NORMAL);
            }
        }
    }
}

GameObjectSelector* Play::getSelectorByCode() {
    for(list<GameObjectSelector*>::iterator iter = gameObjectsSelectors.begin(); iter != gameObjectsSelectors.end() ; iter++)
    {
        if((*iter)->getGameObjectCode() == addGameObjectCode){
            return (*iter);
        }
    }
}

GameObjectSelector *Play::getSelectorByClicked() {
    for(list<GameObjectSelector*>::iterator iter = gameObjectsSelectors.begin(); iter != gameObjectsSelectors.end() ; iter++)
    {
        if((*iter) == clickedObject){
            return (*iter);
        }
    }
}

void Play::increaseMoneyForDefeatingOpponent(int code)
{
    if(code == Opponent::OPPONENT_CODE)
    {
        money += 50;
    }
    else
    {
        money += 100;
    }
}