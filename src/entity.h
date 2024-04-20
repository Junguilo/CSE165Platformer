#ifndef ENTITY_H
#define ENTITY_H
#include <QDebug>
#include <QOpenGLFunctions>
#include <QObject>
#include <QTimer>


class Entity: public QObject
{
    Q_OBJECT
public:
    Entity();
    ~Entity();
    float positionX;
    float positionY;

    //hopefully for when you click on the entity
    //if your mouse pos is in range, it will return true
    float hitboxOneX; //topLeft
    float hitboxOneY;

    float hitboxTwoX;
    float hitboxTwoY; //topRight

    float hitboxThreeX;
    float hitboxThreeY; //bottomLeft

    float hitboxFourX;
    float hitboxFourY; //bottomRight

    void checkHitbox(float x, float y);
protected:
    //stats shared with all entities
    int health;
    int attack;

    bool isHit;

    void setHealth(int health);
    void setAttack(int attack);
    void setPosition(float positionX, float positionY);
    void setHitbox(float hitboxOneX, float hitboxOneY, float hitboxTwoX, float hitboxTwoY, float hitboxThreeX, float hitboxThreeY, float hitboxFourX, float hitboxFourY);
    void setHit(bool isHit);

    int getHealth() const;
    int getAttack() const;
    float getPositionX() const;
    float getPositionY() const;
    float getHitbox() const;
    bool getHit() const;
};

#endif // ENTITY_H
