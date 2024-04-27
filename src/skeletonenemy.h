#ifndef SKELETONENEMY_H
#define SKELETONENEMY_H
#include "entity.h"
#include <QPainter>
#include <QWidget>

class SkeletonEnemy: public Entity
{
public:
    SkeletonEnemy();
    SkeletonEnemy(float positionX, float positionY);
    ~SkeletonEnemy();
    int pointsGiven = 100;

    //Animation Functions
    int frame = 0;
    void draw(QWidget *widget);
    QTimer *animationTimer;
    void stopTimer();
    float normalizedX;
    float normalizedY;
    //All the QFrames
    bool isReloading = false;

    //check if we hit the knife throw frame
    //will spawn the knife at an interval
    bool isThrowing = false;
    //knife throw
    QImage knifeIdleFrame;
    QImage noKnifeIdleFrame;
    QImage skeletonThrow1;
    QImage skeletonThrow2;
    QImage skeletonThrow3;

    //reload
    QImage skeletonReload1;
    QImage skeletonReload2;
    QImage skeletonReload3;

    //hitbox code
    void updateHitbox();
    bool isEnemyHit() const;
public slots:
    void incrementFrame();


};

#endif // SKELETONENEMY_H
