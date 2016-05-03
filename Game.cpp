#include "Game.h"
#include "Opponent.h"
#include "Obstacle.h"
#include "Defense.h"

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
    for(int i=0; i < interfaceObjects.size(); i++)
    {
        delete(interfaceObjects[i]);
    }
    interfaceObjects.clear();
    for(int i=0; i < gameObjects.size(); i++)
    {
        delete(gameObjects[i]);
    }
    gameObjects.clear();

}

void Game:: deleteClickedObject()
{
    int i=0;
    for(i=0; i < gameObjects.size(); i++)
    {
        if(gameObjects[i]==clickedObject)
            break;
    }
    delete(gameObjects[i]);
    gameObjects.erase(gameObjects.begin()+i);
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
                runPlay("maps/"+ getNextMapName()+".izu");
                break;
            case MenuButton::MENU_BUTTON_CODE_LOAD_GAME:
                cout<<"wczytana!"<<endl;
                break;
            case MenuButton::MENU_BUTTON_CODE_CREATE_MAP:
                cout<<"tworz mape!"<<endl;
                runCreator();
                break;
            case MenuButton::MENU_BUTTON_CODE_LIST_OF_MAPS:
                cout<<"lista!"<<endl;
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
    display = al_create_display(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT);
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
    interfaceObjects.push_back(new MenuButton(3, MenuButton::MENU_BUTTON_CODE_LIST_OF_MAPS, "LISTA MAP"));
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
            for(int i=0;i<gameObjects.size();i++)
            {
                int code=gameObjects[i]->getCodeIfClicked(state.x,state.y, &clickedObject);
                if(code != 0)
                {
                    return code;
                }
            }
            for(int i=0; i<interfaceObjects.size();i++)
            {
                int code=interfaceObjects[i]->getCodeIfClicked(state.x,state.y, &clickedObject);
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
                createHPButtons();
                gameState = GAME_STATE_ADD_HP;
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
                for(int i=0; i < gameObjects.size(); i++)
                {
                    gameObjects[i]->displayOnConsole();
                }
                cout<<"-----------------------------------------"<<endl;
                break;
            case HPButton:: HP_BUTTON_CODE_HP6:
                selectedHP=6;
                gameState=GAME_STATE_ADD_DEFENSE;
                break;
            case HPButton:: HP_BUTTON_CODE_HP8:
                selectedHP=8;
                gameState=GAME_STATE_ADD_DEFENSE;
                break;
            case HPButton:: HP_BUTTON_CODE_HP10:
                selectedHP=10;
                gameState=GAME_STATE_ADD_DEFENSE;
                break;
            case GameField::GAME_FIELD_CREATOR_CODE:
                if(gameState==GAME_STATE_ADD_DEFENSE)
                {
                    deleteHPButtons();
                    Defense *defense=new Defense(gameField, selectedHP); //tworze, ale jeszcze nie rysuje
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
                    deleteClickedObject();
                    gameState=GAME_STATE_IDLE;
                }
                break;
            case CreatorButton::CREATOR_BUTTON_CODE_SAVE:
                saveObjects();
                return;
            case CreatorButton::CREATOR_BUTTON_CODE_RETURN:
                return;
            default:
                return;
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
        for(int i=0; i < gameObjects.size(); i++)//iteruje sie po calym wektorze gameObjectow by sprawdzic czy wylosowane pole jest wolne
        {
            if(gameObjects[i]->isItsPosition(*randomRow, *randomColumn))//dla kazdego obiektu sprawdzam cz wylosowane pole to jego pozycja
            {
                freeSquare = false;//nie jest wolne
                break;
            }
        }
    }
    return true;
}

void Game::createHPButtons()
{
    interfaceObjects.push_back(new HPButton(0, HPButton::HP_BUTTON_CODE_HP6, "HP6"));
    interfaceObjects.push_back(new HPButton(1, HPButton::HP_BUTTON_CODE_HP8, "HP8"));
    interfaceObjects.push_back(new HPButton(2, HPButton::HP_BUTTON_CODE_HP10, "HP10"));
    redraw();
}

void Game::deleteHPButtons()
{
    for(int i=0; i < interfaceObjects.size(); i++)
    {
        if(interfaceObjects[i]->getCode()== HPButton::HP_BUTTON_CODE_HP6 || interfaceObjects[i]->getCode()== HPButton::HP_BUTTON_CODE_HP8 || interfaceObjects[i]->getCode()== HPButton::HP_BUTTON_CODE_HP10)
        {
            delete(interfaceObjects[i]);
            interfaceObjects.erase(interfaceObjects.begin()+i);
            i--;
        }
    }
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
    interfaceObjects.push_back(new Legend());
    redraw();
}

void Game::changeState()
{
    switch(gameState)
    {
        case GAME_STATE_ADD_DEFENSE:
            gameField->changeStateToActive();
            for(int i=0; i < interfaceObjects.size(); i++)
            {
                if(interfaceObjects[i]->getCode()== HPButton::HP_BUTTON_CODE_HP6 || interfaceObjects[i]->getCode()== HPButton::HP_BUTTON_CODE_HP8 || interfaceObjects[i]->getCode()== HPButton::HP_BUTTON_CODE_HP10)
                {
                    interfaceObjects[i]->changeColor(al_map_rgb(0,  102, 102));
                }
            }
            clickedObject->changeColor(al_map_rgb(255,  153, 153));
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
    for(int i=0; i < interfaceObjects.size(); i++)
    {
        interfaceObjects[i]->draw();
    }
    for(int i=0; i < gameObjects.size(); i++)
    {
        gameObjects[i]->draw();// po tym jak dodalam cos do worka z obiektami to tu sie dorysuje
    }
    al_flip_display();
}

void Game::saveObjects() {
    ofstream outputStream("maps/"+ getNextMapName() +".izu");
    outputStream << gameObjects.size();
    for(int i=0;i<gameObjects.size();i++){
        gameObjects[i]->saveToStream(&outputStream);
    }
    outputStream.close();
}

void Game::loadObjects(string mapName)
{
    ifstream inputStream(mapName);
    int objectsCount;
    inputStream >> objectsCount; //pobieramy liczbe obiektow
    for(int i=0;i<objectsCount;i++)
    {
        int code;
        inputStream >> code;
        GameObject *gameObject = GameObject::getGameObjectByCode(gameField,code,&inputStream);
        gameObjects.push_back(gameObject);

    }
    inputStream.close();
}

string Game::getNextMapName()
{
    return "map1";
}

void Game::runPlay(string mapName)
{
    deleteObjects();
    gameField = new GameField(GameField::GAME_FIELD_PLAY_CODE);//tworze obiekt gamefield
    loadObjects(mapName);
    drawPlay();
    while(true) {
        switch (getClickedObjectWithCode()) {
            case Button::BUTTON_PLAY_START:
            {
                Play play(this,&gameObjects);
                switch(play.run())
                {

                    case Play::VICTORY_CODE:
                        break;
                    case Play::DEFEAT_CODE:
                        break;
                }
                return;
            }
            default:
                break;
        }
    }
}

void Game::drawPlay()
{
    interfaceObjects.push_back(new Button(400, 500 ,200,100, Button::BUTTON_PLAY_START , "START"));
    interfaceObjects.push_back(gameField);
    redraw();
}