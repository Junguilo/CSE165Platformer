#ifndef ENEMYMONGUS_H
#define ENEMYMONGUS_H
#include "entity.h"

class EnemyMongus: public Entity
{
public:
    EnemyMongus();
    EnemyMongus(float positionX, float positionY);
    ~EnemyMongus();

    //maybe we need these for hitboxes??
    int getEnemyHealth() const;
    int getEnemyAttack() const;
    float getEnemyPositionX() const;
    float getEnemyPositionY() const;
    //Animation Functions
    int frame = 0;
    float scale = 1.0f;
    void draw();

    QTimer *animationTimer;
    QTimer *scaleTimer;
    void stopTimers();

    void updateHitbox();

    //slots are needed to increment vars with QTimer
public slots:
    void incrementFrame();
    void incrementScale();

private:
    void idleFrame();
    void runOneFrame();
    void runTwoFrame();
};

#endif // ENEMYMONGUS_H
