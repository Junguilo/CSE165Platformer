#ifndef ENTITY_H
#define ENTITY_H

#include <QDebug>
#include <QOpenGLFunctions>
#include <QImage>
#include <QPainter>
#include <QObject>
#include <QTimer>

class Entity: public QObject {
    Q_OBJECT
public:
    Entity();
    virtual ~Entity(); // Add virtual destructor for proper cleanup

    float positionX;
    float positionY;

    // Hitbox corners
    float hitboxOneX; // Top-left
    float hitboxOneY;

    float hitboxTwoX; // Top-right
    float hitboxTwoY;

    float hitboxThreeX; // Bottom-left
    float hitboxThreeY;

    float hitboxFourX; // Bottom-right
    float hitboxFourY;

    bool alive;

    // Hit detection function
    void checkHitbox(float x, float y);

    // Entity properties and methods
    int health;
    int attack;
    bool isHit;

    // Setters
    void setHealth(int health);
    void setAttack(int attack);
    void setPosition(float positionX, float positionY);
    void setHitbox(float hitboxOneX, float hitboxOneY, float hitboxTwoX, float hitboxTwoY, float hitboxThreeX, float hitboxThreeY, float hitboxFourX, float hitboxFourY);
    void setHit(bool isHit);

    // Getters
    int getHealth() const;
    int getAttack() const;
    float getPositionX() const;
    float getPositionY() const;
    bool getHit() const;

    // Reducing health
    void reduceHealth();
};

#endif // ENTITY_H
