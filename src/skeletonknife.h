#ifndef SKELETONKNIFE_H
#define SKELETONKNIFE_H
#include "entity.h"
#include "skeletonenemy.h"
#include <QPainter>
#include <QWidget>

class SkeletonKnife:public Entity
{
public:
    SkeletonKnife();
    SkeletonKnife(float positionX, float positionY);
    ~SkeletonKnife();

    //animation variables & Functions
    int frame = 0;
    float scale = 1.0f;
    float normalizedPosX;
    float normalizedPosY;
    QTimer *animationTimer;
    QTimer *scaleTimer;
    QImage throw1;
    QImage throw2;
    QImage throw3;
    QImage throw4;

    QRectF target;
    void draw(QWidget *widget);
    void updateHitbox();

    void updateSkeleThrow(SkeletonEnemy &a);
    bool resetPosition = false;

    bool hitPlayer = false;

public slots:
    void incrementFrame();
    void incrementScale();
};

#endif // SKELETONKNIFE_H
