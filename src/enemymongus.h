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

    //Animation Functions
    int frame = 0;
    float scale = 1.0f;
    void draw();

    QTimer *animationTimer;
    QTimer *scaleTimer;
    QTimer *centerTimer;

    void updateHitbox();

    bool isEnemyHit() const;

    //slots are needed to increment vars with QTimer
public slots:
    void incrementFrame();
    void incrementScale();

private:
    void setCenter();

    void idleFrame();
    void runOneFrame();
    void runTwoFrame();
};

#endif // ENEMYMONGUS_H
