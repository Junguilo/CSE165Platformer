#include "entity.h"

Entity::Entity() {
    qDebug() << "Entity Created";
    alive = true;
}

Entity::~Entity() {
    qDebug() << "Entity Deleted";
}

// Hitbox check function
void Entity::checkHitbox(float x, float y) {
    // Check if (x, y) is within the entity's hitbox
    if (y < hitboxOneY && y > hitboxFourY && x > hitboxOneX && x < hitboxTwoX) {
        qDebug() << "Hit!";
        setHit(true);
    } else {
        // If the coordinates do not match the hitbox, mark isHit as false
        setHit(false);
    }
}

// Setters
void Entity::setHealth(int health) {
    this->health = health;
}

void Entity::setAttack(int attack) {
    this->attack = attack;
}

void Entity::setPosition(float positionX, float positionY) {
    this->positionX = positionX;
    this->positionY = positionY;
}

void Entity::setHitbox(float hitboxOneX, float hitboxOneY, float hitboxTwoX, float hitboxTwoY, float hitboxThreeX, float hitboxThreeY, float hitboxFourX, float hitboxFourY) {
    this->hitboxOneX = hitboxOneX;
    this->hitboxOneY = hitboxOneY;
    this->hitboxTwoX = hitboxTwoX;
    this->hitboxTwoY = hitboxTwoY;
    this->hitboxThreeX = hitboxThreeX;
    this->hitboxThreeY = hitboxThreeY;
    this->hitboxFourX = hitboxFourX;
    this->hitboxFourY = hitboxFourY;
}

// Reducing health
void Entity::reduceHealth() {
    if (health > 0) {
        health--;
    }
    // Check if the entity is dead
    if (health <= 0) {
        alive = false;
        setHit(false); // Set isHit to false when entity dies
    }
}

// Set hit state
void Entity::setHit(bool isHit) {
    this->isHit = isHit;
}

// Getters
int Entity::getHealth() const {
    return health;
}

int Entity::getAttack() const {
    return attack;
}

float Entity::getPositionX() const {
    return positionX;
}

float Entity::getPositionY() const {
    return positionY;
}

bool Entity::getHit() const {
    return isHit;
}

