#include "skeletonknife.h"

SkeletonKnife::SkeletonKnife() {}

SkeletonKnife::SkeletonKnife(float positionX, float positionY){
    setHealth(1);
    setAttack(2);

    setPosition(positionX, positionY);

    throw1.load(":/Images/SkeletonEnemy/KnifeThrow/KnifeThrow1.png");
    throw2.load(":/Images/SkeletonEnemy/KnifeThrow/KnifeThrow2.png");
    throw3.load(":/Images/SkeletonEnemy/KnifeThrow/KnifeThrow3.png");
    throw4.load(":/Images/SkeletonEnemy/KnifeThrow/KnifeThrow4.png");

    //set inital position, will be ran once
    target = QRectF(positionX, positionY, 80,80);
    //animation Timer
    animationTimer = new QTimer();
    connect(animationTimer, &QTimer::timeout, this, &SkeletonKnife::incrementFrame);
    animationTimer->start(100);

    //Scale Increment
    scaleTimer = new QTimer();
    connect(scaleTimer, &QTimer::timeout, this, &SkeletonKnife::incrementScale);
    scaleTimer->start(200);
}

SkeletonKnife::~SkeletonKnife() {
    scaleTimer->stop();
    animationTimer->stop();
    qDebug() << "deletedKnife";
}

void SkeletonKnife::incrementFrame(){
    frame++;
}

void SkeletonKnife::incrementScale(){
    // Define your scaling factor here
    qreal scaleFactor = 1.15; // for example, scales the rect by 10% each time

    // Get the current position and size of the QRectF
    qreal x = target.x();
    qreal y = target.y();
    qreal width = target.width();
    qreal height = target.height();

    // Calculate new dimensions based on the scaling factor
    qreal newWidth = width * scaleFactor;
    qreal newHeight = height * scaleFactor;

    // Calculate the center point of the QRectF
    qreal centerX = x + width / 2;
    qreal centerY = y + height / 2;

    // Adjust the position to keep the center fixed
    x = centerX - newWidth / 2;
    y = centerY - newHeight / 2;
    //qDebug() << "X Value" << x;
   // qDebug() << "Y Value" << y;
    //qDebug() << "--------";
    //stops the scale if we reach a certain point, will hit the player here
    if(x < 25.0f && y < -40.0f){
        //hit player here
        //we dont stop the timers because we'll reuse this knife
        //sets the skeletonEnemy's knife draw to be false, then hide the knife and reset position/scale
        resetPosition = true;
        hitPlayer = true;
    }

    // Update the QRectF with the new dimensions
    target.setRect(x, y, newWidth, newHeight);
}
void SkeletonKnife::updateSkeleThrow(SkeletonEnemy &a){
    if(resetPosition){
        a.isThrowing = false; //will hide the knife
        target = QRectF(positionX, positionY, 80,80); //resets position
        resetPosition = false;
    }
}

void SkeletonKnife::draw(QWidget *widget){
    QPainter p(widget); // Using the widget as the paint device

    QImage currentImage;
    switch(frame){
    case 0:
        currentImage = throw1;
        break;
    case 1:
        currentImage = throw2;
        break;
    case 2:
        currentImage = throw3;
        break;
    case 3:
        currentImage = throw4;
        break;
    default:
        currentImage = throw1;
        frame=0;
    }

    QImage image(currentImage);
    p.drawImage(target, image);
}
