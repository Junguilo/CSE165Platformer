#include "skeletonenemy.h"

SkeletonEnemy::SkeletonEnemy() {}

SkeletonEnemy::SkeletonEnemy(float positionX, float positionY){
    setHealth(1);
    setAttack(0);

    setPosition(positionX, positionY);
    //Load the enemy frames for knife throwing
    knifeIdleFrame.load(":/Images/SkeletonEnemy/ThrowSprite/SkeletonThrow1.png");
    noKnifeIdleFrame.load(":/Images/SkeletonEnemy/ThrowSprite/SkeletonThrow5.png");
    skeletonThrow1.load(":/Images/SkeletonEnemy/ThrowSprite/SkeletonThrow2.png");
    skeletonThrow2.load(":/Images/SkeletonEnemy/ThrowSprite/SkeletonThrow3.png");
    skeletonThrow3.load(":/Images/SkeletonEnemy/ThrowSprite/SkeletonThrow4.png");

    //knife reloading
    skeletonReload1.load(":/Images/SkeletonEnemy/ReloadSprite/SkeletonReload2.png");
    skeletonReload2.load(":/Images/SkeletonEnemy/ReloadSprite/SkeletonReload3.png");
    skeletonReload3.load(":/Images/SkeletonEnemy/ReloadSprite/SkeletonReload4.png");

    qDebug() << "Enemy Created with these Stats";
    qDebug() << "Health: " << getHealth();
    qDebug() << "Attack: " << getAttack();
    qDebug() << "PositionX: " << getPositionX();
    qDebug() << "PositionY: " << getPositionY();

    //hitboxes
    // Translate position to center //800 is the height and width of the screen
    float centerX = positionX - 800 / 2.0f;
    float centerY = 800 / 2.0f - positionY;
    // Scale to range -1 to 1
    normalizedX = (2.0f * centerX) / 800;
    normalizedY = (2.0f * centerY) / 800;

    setHitbox(-0.095f, 0.255f,
                0.39f, 0.255f,
                0.39f, -0.5625f,
                -0.095f, -0.5625f);

    //animation
    animationTimer = new QTimer();
    connect(animationTimer, &QTimer::timeout, this, &SkeletonEnemy::incrementFrame);
    animationTimer->start(150);
}

SkeletonEnemy::~SkeletonEnemy(){
    animationTimer->stop();
    qDebug() << "Skele DEAD";
}

bool SkeletonEnemy::isEnemyHit() const{
    return getHit();
}

void SkeletonEnemy::incrementFrame(){
    frame++;
}

//update hitboxes later
void SkeletonEnemy::updateHitbox(){
    glColor3f(1.0f, 0.992f, 0.518f);
    glBegin(GL_LINES);
    glVertex2f(hitboxOneX, hitboxOneY);
    glVertex2f(hitboxTwoX, hitboxTwoY);
    glEnd();

    glColor3f(1.0f, 0.992f, 0.518f);
    glBegin(GL_LINES);
    glVertex2f(hitboxTwoX, hitboxTwoY);
    glVertex2f(hitboxThreeX, hitboxThreeY);
    glEnd();

    glColor3f(1.0f, 0.992f, 0.518f);
    glBegin(GL_LINES);
    glVertex2f(hitboxThreeX, hitboxThreeY);
    glVertex2f(hitboxFourX, hitboxFourY);
    glEnd();

    glColor3f(1.0f, 0.992f, 0.518f);
    glBegin(GL_LINES);
    glVertex2f(hitboxFourX, hitboxFourY);
    glVertex2f(hitboxOneX, hitboxOneY);
    glEnd();
}

void SkeletonEnemy::draw(QWidget *widget){
    QPainter p(widget); // Using the widget as the paint device
    QRectF target(getPositionX(),getPositionY(),320,320);

    //checks if the skeleman already threw a knife
    QImage currentImage;
    if(!isReloading){
        switch(frame){
        case 0:
            currentImage = knifeIdleFrame;
            break;
        case 1:
            currentImage = skeletonThrow1;
            break;
        case 2: //this frame is where the knife should be thrown
            isThrowing = true;
            currentImage = skeletonThrow2;
            break;
        case 3:
            currentImage = skeletonThrow3;
            break;
        case 4:
            currentImage = noKnifeIdleFrame;
            break;
        case 5: //wait a bit before reloading,
            //dont want another knife on screen before the other one
            // or turn this into an if statement
            currentImage = noKnifeIdleFrame;
            break;
        case 6:
            currentImage = noKnifeIdleFrame;
            break;
        case 7:
            currentImage = noKnifeIdleFrame;
            break;
        case 8:
            currentImage = noKnifeIdleFrame;
            break;
        case 9:
            currentImage = noKnifeIdleFrame;
            break;
        case 10:
            currentImage = noKnifeIdleFrame;
            break;
        default:
            currentImage = noKnifeIdleFrame;
            isReloading = true;
            frame = 0;
        }
    } else {
        switch(frame){
        case 0:
            currentImage = noKnifeIdleFrame;
            break;
        case 1:
            currentImage = skeletonReload1;
            break;
        case 2:
            currentImage = skeletonReload2;
            break;
        case 3:
            currentImage = skeletonReload3;
            break;
        case 4:
            currentImage = knifeIdleFrame;
            break;
        default:
            currentImage = knifeIdleFrame;
            isReloading = false;
            frame = 0;
        }
    }

    QImage image(currentImage);
    p.drawImage(target, image);
}

