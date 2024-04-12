#include "enemymongus.h"

EnemyMongus::EnemyMongus() {
    qDebug() << "Enemy Created with No Stats";
}

EnemyMongus::EnemyMongus(int health, int attack, float positionX, float positionY){
    setHealth(health);
    setAttack(attack);
    setPosition(positionX, positionY);
    qDebug() << "Enemy Created with these Stats";
    qDebug() << "Health: " << getHealth();
    qDebug() << "Attack: " << getAttack();
    qDebug() << "PositionX: " << getPositionX();
    qDebug() << "PositionY: " << getPositionY();
    draw();
}

int EnemyMongus::getEnemyHealth() const{
    return getHealth();
}

int EnemyMongus::getEnemyAttack() const{
    return getAttack();
}

float EnemyMongus::getEnemyPositionX() const{
    return getPositionX();
}

float EnemyMongus::getEnemyPositionY() const{
    return getPositionY();
}

void EnemyMongus::draw(){

    //test draw the frame
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.5 + getPositionX(), -0.5 + getPositionY());   // Bottom-left vertex
    glVertex2f(0.5 + getPositionX(), -0.5+ getPositionY());    // Bottom-right vertex
    glVertex2f(0.5 + getPositionX(), 0.5+ getPositionY());     // Top-right vertex
    glVertex2f(-0.5 + getPositionX(), 0.5+ getPositionY());    // Top-left vertex
    glEnd();
}
