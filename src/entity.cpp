#include "entity.h"

Entity::Entity() {
    qDebug() << "Entity Created";
}


Entity::~Entity(){
    qDebug() << "Entity Deleted";
}

//setters
void Entity::setHealth(int health){
    this->health = health;
}

void Entity::setAttack(int attack){
    this->attack = attack;
}

void Entity::setPositionX(float positionX){
    this->positionX = positionX;
}

void Entity::setPositionY(float positionY){
    this->positionY = positionY;
}

void Entity::setPosition(float positionX, float positionY){
    this->positionX = positionX;
    this->positionY = positionY;
}

void Entity::setHitbox(float hitboxOne, float hitboxTwo, float hitboxThree, float hitboxFour){
    this->hitboxOne = hitboxOne;
    this->hitboxTwo = hitboxTwo;
    this->hitboxThree = hitboxThree;
    this->hitboxFour = hitboxFour;
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

