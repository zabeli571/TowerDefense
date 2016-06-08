#include "Game.h"
#include "Opponent.h"
#include "Obstacle.h"
#include "Defense.h"
#include "Text.h"
#include "NumberChangeButton.h"
#include "NumberField.h"
#include "Pause.h"
#include "Legend.h"
#include "MenuButton.h"
#include "CreatorButton.h"

Game::Game()
{
    cout<<"konstruktor Game"<<endl;
    gameState=GAME_STATE_IDLE;
}

Game::~Game()
{
    deleteObjects();
    cout<<"destruktor Game"<<endl;
    al_uninstall_mouse();
    al_destroy_font(font);
    al_destroy_display(display);
}

void Game::deleteObjects()//iteruje sie po obu wektorach i usuwam
{
    for(list<MainObject*>::iterator iter = interfaceObjects.begin(); iter != interfaceObjects.end() ; iter++)
    {
        delete(*iter);
    }
    interfaceObjects.clear();
    for(list<GameObject*>::iterator iter = gameObjects.begin(); iter != gameObjects.end() ; iter++)
    {
        delete(*iter);
    }
    gameObjects.clear();

}

void Game:: deleteObject(MainObject *gameObject)
{
    list<GameObject*>::iterator iter;
    for(iter = gameObjects.begin(); iter != gameObjects.end() ; iter++)
    {
        if((*iter)==gameObject)
            break;
    }
    delete(*iter);
    gameObjects.erase(iter);
}

void Game::run()
{
    initAllegro();
    while(true){
        runMenu();
        switch(getClickedObjectWithCode())
        {
            case MenuButton::MENU_BUTTON_CODE_NEW_GAME:
                cout<<"nowa gra!"<<endl;
                runPlay("maps/"+ getNextMapName()+".izu", false);
                break;
            case MenuButton::MENU_BUTTON_CODE_LOAD_GAME:
                cout<<"wczytana!"<<endl;
                runPlay("saves/save1.izusave", true);
                break;
            case MenuButton::MENU_BUTTON_CODE_CREATE_MAP:
                cout<<"tworz mape!"<<endl;
                runCreator();
                break;
            case MenuButton::MENU_BUTTON_CODE_LEGEND:
                {
                    cout<<"lista!"<<endl;
                    Legend legend;
                    legend.draw();
                    legend.getButtonCodeWhenClicked();
                }
                break;
            case MenuButton::MENU_BUTTON_CODE_EXIT:
                return;
        }
        deleteObjects();
    }

}

void Game::initAllegro() {
    if(!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return;
    }
    display = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
    if(!display) {
        fprintf(stderr, "failed to create display!\n");
        return;
    }
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_mouse();
    al_init_image_addon();
}

void Game::runMenu()
{
    interfaceObjects.push_back(new MenuButton(0, MenuButton::MENU_BUTTON_CODE_NEW_GAME,"NOWA GRA"));//dodaje przyciski do wektora
    interfaceObjects.push_back(new MenuButton(1, MenuButton::MENU_BUTTON_CODE_LOAD_GAME,"WCZYTAJ GRE"));
    interfaceObjects.push_back(new MenuButton(2, MenuButton::MENU_BUTTON_CODE_CREATE_MAP, "TWORZENIE MAPY"));
    interfaceObjects.push_back(new MenuButton(3, MenuButton::MENU_BUTTON_CODE_LEGEND, "OPIS GRY"));
    interfaceObjects.push_back(new MenuButton(4, MenuButton::MENU_BUTTON_CODE_EXIT,"WYJDZ"));
    redraw();
}

int Game::getClickedObjectWithCode()
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
            for(list<GameObject*>::iterator iter = gameObjects.begin(); iter != gameObjects.end() ; iter++)
            {
                int code=(*iter)->getCodeIfClicked(state.x,state.y, &clickedObject);
                if(code != 0)
                {
                    return code;
                }
            }
            for(list<MainObject*>::iterator iter = interfaceObjects.begin(); iter != interfaceObjects.end() ; iter++)
            {
                int code=(*iter)->getCodeIfClicked(state.x,state.y, &clickedObject);
                if(code != 0)
                {
                    return code;
                }
            }
        }
    }
}

void Game::runCreator()
{
    drawCreator();
    while(true){
        switch(getClickedObjectWithCode())
        {
            case CreatorButton::CREATOR_BUTTON_CODE_ADD_TOWER:
//                createHPButtons();
//                gameState = GAME_STATE_ADD_HP;
                gameState=GAME_STATE_ADD_DEFENSE;
                break;
            case CreatorButton::CREATOR_BUTTON_CODE_ADD_OPPONENT:
                gameState = GAME_STATE_ADD_OPPONENT;
                break;
            case CreatorButton::CREATOR_BUTTON_CODE_ADD_OBSTACLE:
                gameState = GAME_STATE_ADD_OBSTACLE;
                break;
            case CreatorButton::CREATOR_BUTTON_CODE_REMOVE_OBJECT:
                gameState = GAME_STATE_REMOVE_OBJECT;
                break;
            case CreatorButton::CREATOR_BUTTON_CODE_RANDOM_OPPONENT:
                int randomOpponentRow, randomOpponentColumn;
                if (getFreeRandomSquare(&randomOpponentRow, &randomOpponentColumn)) {
                    gameObjects.push_back(new Opponent(gameField, randomOpponentRow, randomOpponentColumn));
                }
                else {
                    cout << "Brak wolnego miejsca na mapie"<<endl;
                }
                break;
            case CreatorButton::CREATOR_BUTTON_CODE_RANDOM_OBSTACLE:
                int randomObstacleRow, randomObstacleColumn;
                if (getFreeRandomSquare(&randomObstacleRow, &randomObstacleColumn))//wartosci zapisza sie w miejscach na ktore wskazuja
                {
                    gameObjects.push_back(new Obstacle(gameField, randomObstacleRow, randomObstacleColumn));
                }
                else {
                    cout << "Brak wolnego miejsca na mapie"<<endl;
                }
                break;
            case CreatorButton::CREATOR_BUTTON_CODE_DISPLAY:
                cout<<"-----------------------------------------"<<endl;
                for(list<GameObject*>::iterator iter = gameObjects.begin(); iter != gameObjects.end() ; iter++)
                {
                    (*iter)->displayOnConsole();
                }
                cout<<"-----------------------------------------"<<endl;
                break;
            case GameField::GAME_FIELD_CREATOR_CODE:
                if(gameState==GAME_STATE_ADD_DEFENSE)
                {
                    Defense *defense=new Defense(gameField); //tworze, ale jeszcze nie rysuje
                    gameObjects.push_back(defense);//dodaje do worka z obiektami
                    gameState=GAME_STATE_IDLE;
                }
                if(gameState==GAME_STATE_ADD_OPPONENT)
                {
                    Opponent *opponent=new Opponent(gameField);
                    gameObjects.push_back(opponent);
                    gameState=GAME_STATE_IDLE;
                }
                if(gameState==GAME_STATE_ADD_OBSTACLE)
                {
                    Obstacle *obstacle=new Obstacle (gameField);
                    gameObjects.push_back(obstacle);
                    gameState=GAME_STATE_IDLE;
                }
                break;
            case Defense::DEFENSE_CODE:
            case Opponent::OPPONENT_CODE:
            case Obstacle::OBSTACLE_CODE:
                if(gameState==GAME_STATE_REMOVE_OBJECT)
                {
                    deleteObject(clickedObject);
                    gameState=GAME_STATE_IDLE;
                }
                break;
            case CreatorButton::CREATOR_BUTTON_CODE_SAVE: //klikam zapisz
                saveObjects();
                return;
            case CreatorButton::CREATOR_BUTTON_CODE_RETURN:
                return;
            case NumberChangeButton::NUMBER_CHANGE_BUTTON_INCREASE_MONEY:
                money+=50;
                break;
            case NumberChangeButton::NUMBER_CHANGE_BUTTON_DECREASE_MONEY:
                if(money >=50)
                {
                    money-=50;
                }
                break;
            case NumberChangeButton::NUMBER_CHANGE_BUTTON_INCREASE_WAVES:
                waves+=1;
                break;
            case NumberChangeButton::NUMBER_CHANGE_BUTTON_DECREASE_WAVES:
                if(waves >=1)
                {
                    waves-=1;
                }
                break;
            case NumberChangeButton::NUMBER_CHANGE_BUTTON_INCREASE_FREQUENCY:
                frequency+=1;
                break;
            case NumberChangeButton::NUMBER_CHANGE_BUTTON_DECREASE_FREQUENCY:
                if(frequency >=1)
                {
                    frequency-=1;
                }
                break;
            default:
                break;
        }
        changeState();
    }
}

bool Game::getFreeRandomSquare(int *randomRow,int *randomColumn) {
    bool freeSquare = false;
    if(gameObjects.size() == gameField->getSquareCount())
    {
        return false;
    }
    while(!freeSquare)
    {
        gameField->getRandomSquare(randomRow, randomColumn);//losuje randomowe pole
        freeSquare = true;
        for(list<GameObject*>::iterator iter = gameObjects.begin(); iter != gameObjects.end() ; iter++)//iteruje sie po calym wektorze gameObjectow by sprawdzic czy wylosowane pole jest wolne
        {
            if((*iter)->isItsPosition(*randomRow, *randomColumn))//dla kazdego obiektu sprawdzam cz wylosowane pole to jego pozycja
            {
                freeSquare = false;//nie jest wolne
                break;
            }
        }
    }
    return true;
}

void Game::drawCreator() {
    //cout << "jestem w runCreator!" << endl;
    deleteObjects();
    gameField = new GameField(GameField::GAME_FIELD_CREATOR_CODE);//tworze obiekt gamefield
    interfaceObjects.push_back(new CreatorButton(0, CreatorButton::CREATOR_BUTTON_CODE_ADD_TOWER, "DODAJ WIEZE"));//dodaje przyciski do wektora, przekazuje nr code name do konstruktora buttona
    interfaceObjects.push_back(new CreatorButton(1, CreatorButton::CREATOR_BUTTON_CODE_ADD_OPPONENT, "DODAJ PRZECIWNIKA"));
    interfaceObjects.push_back(new CreatorButton(2, CreatorButton::CREATOR_BUTTON_CODE_ADD_OBSTACLE, "DODAJ PRZESZKODE"));
    interfaceObjects.push_back(new CreatorButton(3, CreatorButton::CREATOR_BUTTON_CODE_REMOVE_OBJECT, "USUN OBIEKT"));
    interfaceObjects.push_back(new CreatorButton(4, CreatorButton::CREATOR_BUTTON_CODE_RANDOM_OPPONENT, "LOSUJ PRZECIWNIKA"));
    interfaceObjects.push_back(new CreatorButton(5, CreatorButton::CREATOR_BUTTON_CODE_RANDOM_OBSTACLE, "LOSUJ PRZESZKODE"));
    interfaceObjects.push_back(new CreatorButton(6, CreatorButton::CREATOR_BUTTON_CODE_DISPLAY, "LISTA OBIEKTOW"));
    interfaceObjects.push_back(new CreatorButton(7, CreatorButton::CREATOR_BUTTON_CODE_SAVE, "ZAPISZ"));
    interfaceObjects.push_back(new CreatorButton(8, CreatorButton::CREATOR_BUTTON_CODE_RETURN, "WROC DO MENU"));
    interfaceObjects.push_back(gameField);
    interfaceObjects.push_back(new Text(350,345,30,"Liczba monet",ALLEGRO_ALIGN_CENTRE));
    interfaceObjects.push_back(new NumberChangeButton(250,380,NumberChangeButton::NUMBER_CHANGE_BUTTON_DECREASE_MONEY,false));
    interfaceObjects.push_back(new NumberChangeButton(400,380,NumberChangeButton::NUMBER_CHANGE_BUTTON_INCREASE_MONEY,true));
    interfaceObjects.push_back(new NumberField(350,390,30,&money));
    interfaceObjects.push_back(new Text(350,435,30,"Liczba  fal przeciwnikow",ALLEGRO_ALIGN_CENTRE));
    interfaceObjects.push_back(new NumberChangeButton(250,470,NumberChangeButton::NUMBER_CHANGE_BUTTON_DECREASE_WAVES,false));
    interfaceObjects.push_back(new NumberChangeButton(400,470,NumberChangeButton::NUMBER_CHANGE_BUTTON_INCREASE_WAVES,true));
    interfaceObjects.push_back(new NumberField(350,480,30,&waves));
    interfaceObjects.push_back(new Text(350,525,30,"Czestotliwosc fal przeciwnikow [s]",ALLEGRO_ALIGN_CENTRE));
    interfaceObjects.push_back(new NumberChangeButton(250,560,NumberChangeButton::NUMBER_CHANGE_BUTTON_DECREASE_FREQUENCY,false));
    interfaceObjects.push_back(new NumberChangeButton(400,560,NumberChangeButton::NUMBER_CHANGE_BUTTON_INCREASE_FREQUENCY,true));
    interfaceObjects.push_back(new NumberField(350,570,30,&frequency));
    redraw();
}

void Game::changeState()
{
    switch(gameState)
    {
        case GAME_STATE_ADD_DEFENSE:
            gameField->changeStateToActive();
            break;
        case GAME_STATE_ADD_OPPONENT:
        case GAME_STATE_ADD_OBSTACLE:
        case GAME_STATE_REMOVE_OBJECT:
            gameField->changeStateToActive();//pole rozowe
            break;
        case GAME_STATE_IDLE:
            gameField->changeStateToInactive();//pole zwykle
            break;
        default:
            break;
    }
    redraw();
}

void Game::redraw()
{
    al_clear_to_color(al_map_rgb(153,204,255));
    for(list<MainObject*>::iterator iter = interfaceObjects.begin(); iter != interfaceObjects.end() ; iter++)
    {
        (*iter)->draw();
    }
    for(list<GameObject*>::iterator iter = gameObjects.begin(); iter != gameObjects.end() ; iter++)//iteruje sie po calym wektorze gameObjectow by sprawdzic czy wylosowane pole jest wolne
    {
        (*iter)->draw();// po tym jak dodalam cos do worka z obiektami to tu sie dorysuje
    }
    al_flip_display();
}

void Game::saveObjects() //gdy wybierzemy przycisk zapisz
{
    ofstream outputStream("maps/"+ getNextMapName() +".izu"); // obiekt strumien-outputStream klasy ofstream, do konstruktora podaje sciezke

    outputStream << money << " " << waves << " " << frequency << " ";
    outputStream << gameObjects.size(); //zapisujemy ilosc obiektow
    for(list<GameObject*>::iterator iter = gameObjects.begin(); iter != gameObjects.end() ; iter++)
    {
        (*iter)->saveToStream(&outputStream);
    }
    outputStream.close(); //zamyka strumien
}

string Game::getNextMapName()
{
    return "map1"; //narazie mam 1 mape
}

void Game::runPlay(string mapName, bool isLoad)
{
    deleteObjects();
    Statistics statistics; //tworzymy obiekt statistics
    Play play(mapName,this,&gameObjects, &interfaceObjects, &statistics, isLoad); //tworze nowy obiekt play przekazuje game i adres do wektora obiektow wczytanych z pliku
    int score = play.run(); //zaczyna sie gra
    if(score == Pause::EXIT_CODE)
    {
        return;
    }
    else
    {
        statistics.setPlayFinished(score);
        statistics.draw(); //rysuje statystyki
        switch (statistics.getButtonCodeWhenClicked())
        {
            case Statistics::BACK_CODE:
                return; //wychodze z tej funkcji, wiec az do menu
        }
    }
}