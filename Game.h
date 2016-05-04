#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include "Button.h"
#include <vector>
#include "Constants.h"
#include "MenuButton.h"
#include "CreatorButton.h"
#include "GameObject.h"
#include "HPButton.h"
#include "Legend.h"
#include "Play.h"
#include "Statistics.h"
#include <fstream>

using namespace std;

class Game
{
    friend class Play;
private:
    static const int GAME_STATE_IDLE = 0;
    static const int GAME_STATE_ADD_DEFENSE=1;
    static const int GAME_STATE_ADD_OPPONENT=2;
    static const int GAME_STATE_ADD_OBSTACLE=3;
    static const int GAME_STATE_REMOVE_OBJECT=4;
    static const int GAME_STATE_ADD_HP=5;
    int gameState;
    int selectedHP;
    GameField *gameField;
    vector<MainObject*> interfaceObjects;//button,gamefield
    vector<GameObject*> gameObjects;//tylko defense,opponents,obstacles
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_FONT *font=NULL;
    MainObject *clickedObject;
public:
    Game();
    ~Game();
    void run();
private:
    int getClickedObjectWithCode();
    void runCreator();
    void initAllegro();
    void runMenu();
    void deleteObjects();
    void drawCreator();
    void createHPButtons();
    void deleteHPButtons();
    void changeState();
    void redraw();
    void deleteClickedObject();
    bool getFreeRandomSquare(int *randomRow,int *randomColumn);

    void saveObjects();
    string getNextMapName();
    void runPlay(string mapName);
    void drawPlay();

    void loadObjects(string mapName);
};
#endif
