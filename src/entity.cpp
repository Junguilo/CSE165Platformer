#include "entity.h"

Entity::Entity() {
    qDebug() << "Entity Created";
}


Entity::~Entity(){
    qDebug() << "Entity Deleted";
}


//this function will be used in mouseClick Event,
void Entity::checkHitbox(float x, float y){
    //remember
    //hitboxOne, (x, y) -> hitboxTwo (x, y) is the top Check; Y (posY < Y)
    //hitboxTwo -> hitboxThree is the right check; X (posX < X)
    //hitboxThree -> hitboxFour is the bottom check; Y (posY > Y)
    //hitboxFour -> hitboxOne is the left check; X (posX > Y)
    if(y < hitboxOneY && y > hitboxFourY && x > hitboxOneX && x < hitboxTwoX){
        qDebug() << "Hit!";
        setHit(true);
    }
}

//setters
void Entity::setHealth(int health){
    this->health = health;
}

void Entity::setAttack(int attack){
    this->attack = attack;
}

void Entity::setPosition(float positionX, float positionY){
    this->positionX = positionX;
    this->positionY = positionY;
}

void Entity::setHitbox(float hitboxOneX, float hitboxOneY, float hitboxTwoX, float hitboxTwoY, float hitboxThreeX, float hitboxThreeY, float hitboxFourX, float hitboxFourY){
    this->hitboxOneX = hitboxOneX;
    this->hitboxOneY = hitboxOneY;
    this->hitboxTwoX = hitboxTwoX;
    this->hitboxTwoY = hitboxTwoY;
    this->hitboxThreeX = hitboxThreeX;
    this->hitboxThreeY = hitboxThreeY;
    this->hitboxFourX = hitboxFourX;
    this->hitboxFourY = hitboxFourY;
}

void Entity::setHit(bool isHit){
    this->isHit = isHit;
}

//Getters
int Entity::getHealth() const{
    return health;
}

int Entity::getAttack() const{
    return attack;
}

float Entity::getPositionX() const{
    return positionX;
}

float Entity::getPositionY() const{
    return positionY;
}

bool Entity::getHit() const{
    return isHit;
}

