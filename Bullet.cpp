#include "Bullet.h"
#include "Opponent.h"
#include "Play.h"

Bullet::Bullet(GameField *gameField, int x, int y) : GameObject(gameField,x,y,true)
{
//    cout<<"\tkonstruktor Bullet"<<endl;
    code = BULLET_CODE;
    hp=1;
    initialHP = hp;
    allegroColor=al_map_rgb(204,0,0);
    image = al_load_bitmap("bitmaps/bullet.png");
    imageHalfHP = al_load_bitmap("bitmaps/bullet.png");

    alreadyPunched = false;

    int shrinkValue = xLength/2; //pomniejszam za duza pestke
    xLength -= shrinkValue;
    yLength -= shrinkValue;
    this->x += shrinkValue/2;
    this->y += shrinkValue/2;
}

Bullet::Bullet(GameField *gameField, ifstream *inputStream, bool exact) : GameObject(gameField,inputStream,exact)
{
    code = BULLET_CODE;
    image = al_load_bitmap("bitmaps/bullet.png");
    imageHalfHP = al_load_bitmap("bitmaps/bullet.png");
    int shrinkValue = xLength/2;
    xLength -= shrinkValue;
    yLength -= shrinkValue;

    int k;
    *inputStream >> k;
    alreadyPunched = k==1;
}

Bullet::~Bullet()
{
//    cout<<"destruktor Bullet"<<endl;
}

void Bullet::collisionWith(GameObject *anotherObject)
{
    anotherObject->collisionWithBullet(this);
}

void Bullet::collisionWithObstacle(Obstacle *obstacle)
{
    //brak interakcji
}

void Bullet::collisionWithOpponent(Opponent *opponent)
{
    if(!alreadyPunched) //bullet uderza tylko raz i znika
    {
        opponent->hp-=2;
        hp--;
        alreadyPunched = true;
    }
}

void Bullet::collisionWithDefense(Defense *defense)
{
    //brak interakcji
}

void Bullet::doAction(Play *play)
{
    //brak interakcji
}

void Bullet::collisionWithBullet(Bullet *bullet)
{
    //brak interakcji
}

void Bullet::move()
{
    x+=5;
}

void Bullet::saveToStreamExact(ofstream *outputStream) {
    GameObject::saveToStreamExact(outputStream);
    *outputStream << " " << (alreadyPunched?1:0);
}