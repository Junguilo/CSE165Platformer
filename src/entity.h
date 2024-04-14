#ifndef ENTITY_H
#define ENTITY_H
#include <QDebug>
#include <QOpenGLFunctions>
#include <QObject>

class Entity: public QObject
{
    Q_OBJECT
public:
    Entity();
    ~Entity();
    float positionX;
    float positionY;

protected:
    //stats shared with all entities
    int health;
    int attack;

    //hopefully for when you click on the entity
    //if your mouse pos is in range, it will return true
    float hitboxOne; //topLeft
    float hitboxTwo; //topRight
    float hitboxThree; //bottomLeft
    float hitboxFour; //bottomRight

    bool isHit;

    void setHealth(int health);
    void setAttack(int attack);
    void setPositionX(float positionX);
    void setPositionY(float positionY);
    void setPosition(float positionX, float positionY);
    void setHitbox(float hitboxOne, float hitboxTwo, float hitboxThree, float hitboxFour);
    void setHit(bool isHit);

    int getHealth() const;
    int getAttack() const;
    float getPositionX() const;
    float getPositionY() const;
    float getHitbox() const;
    bool getHit() const;
};

#endif // ENTITY_H
