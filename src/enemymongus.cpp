#include "enemymongus.h"

EnemyMongus::EnemyMongus() {
    qDebug() << "Enemy Created with No Stats, please add Stats";
}

EnemyMongus::EnemyMongus(float positionX, float positionY){
    //the Health and Attack Vals of this enemy is hardcoded.
    setHealth(10);
    setAttack(2);

    setPosition(positionX, positionY);
    setHitbox(-0.2625f, 0.1625f, //tl
              0.0525f, 0.1625f,  //tr
              0.0525f, -0.1625f,  //br
              -0.2625f, -0.1625f); //bl

    qDebug() << "Enemy Created with these Stats";
    qDebug() << "Health: " << getHealth();
    qDebug() << "Attack: " << getAttack();
    qDebug() << "PositionX: " << getPositionX();
    qDebug() << "PositionY: " << getPositionY();
    //sounds

    //Timer for created Mungus' Animation
    //This timer will increment the Frame variable and can be used for animation
    animationTimer = new QTimer();
    connect(animationTimer, &QTimer::timeout, this, &EnemyMongus::incrementFrame);
    //1000ms is 1 second, will draw each frame every 0.5 seconds
    animationTimer->start(200);

    //Scale Increment
    scaleTimer = new QTimer();
    connect(scaleTimer, &QTimer::timeout, this, &EnemyMongus::incrementScale);
    scaleTimer->start(200);
}

EnemyMongus::~EnemyMongus(){
    //when a mongus dies, add points to the qtText
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

//Draw Hitbox Lines for Debugging
void EnemyMongus::updateHitbox(){
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

    //update hitboxes for scaling and position
    setHitbox((-0.2625f + getPositionX()) * scale, (0.1625f + getPositionY()) * scale,  // tl
              (0.0525f + getPositionX()) * scale, (0.1625f + getPositionY()) * scale,  // tr
              (0.0525f + getPositionX()) * scale, (-0.1625f + getPositionY()) * scale, // br
              (-0.2625f + getPositionX()) * scale, (-0.1625f + getPositionY()) * scale);// bl


}


//For SLOT Timer Functions
void EnemyMongus::incrementFrame(){
    frame++;
}

void EnemyMongus::incrementScale(){
    scale += 0.15f;
    qDebug() << scale;

    if(scale >= 5.0f){
        scaleTimer->stop();
        animationTimer->stop();
        frame = 0;
    }
}
//With an animator(draw()), we can take these functions and make a switch statement
//in order to change the frame of the pictures.
//Switch statement? or Timer used in an if statement in order to animate.
//We will probably need to find a way to get the hitboxes of the entities.
void EnemyMongus::draw(){
    //will make this the animator,
    //all the frames will be drawn as functions.
    //Should be swapped for a statemachine for (IDLE) and (RUNNING), animations
    switch(frame){
    case 0:
        idleFrame();
        break;
    case 1:
        runOneFrame();
        break;
    case 2:
        runTwoFrame();
        break;
    default:
        runOneFrame();
        frame = 1;
    }

}


//====================================
//==================FRAMES
//====================================
void EnemyMongus::idleFrame(){
    //base x is L(-0.1975) & R(0.0325)
    //will swap later

    //----- Idle State ---
    //Head
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f((-0.1975 + getPositionX()) * scale , (0.07755 + getPositionY()) * scale);   // Bottom-left vertex
    glVertex2f((0.0325 + getPositionX()) * scale, (0.0775+ getPositionY()) * scale);    // Bottom-right vertex
    glVertex2f((-0.0175 + getPositionX()) * scale, (0.15 + getPositionY()) * scale);     // Top-right vertex
    glVertex2f((-0.15 + getPositionX()) * scale, (0.15 + getPositionY()) * scale);    // Top-left vertex
    glEnd();

    //body
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f((-0.1975 + getPositionX()) * scale, (-0.10 + getPositionY()) * scale);   // Bottom-left vertex
    glVertex2f((0.0325 + getPositionX()) * scale, (-0.10+ getPositionY()) * scale);    // Bottom-right vertex
    glVertex2f((0.0325 + getPositionX()) * scale, (0.0775+ getPositionY()) * scale);    // Top-right vertex
    glVertex2f((-0.1975 + getPositionX()) * scale, (0.07755 + getPositionY()) * scale);   // Top-Left vertex
    glEnd();

    //left leg
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f((-0.1975 + getPositionX()) * scale, (-0.20 + getPositionY() + 0.045) * scale);
    glVertex2f((-0.1275 + getPositionX()) * scale, (-0.20 + getPositionY() + 0.045) * scale);
    glVertex2f((-0.1275 + getPositionX()) * scale, (-0.10 + getPositionY() + 0.045) * scale);
    glVertex2f((-0.1975 + getPositionX()) * scale, (-0.10 + getPositionY() + 0.045) * scale);
    glEnd();

    //left foot
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f((-0.255 + getPositionX()) * scale, (-0.20 + getPositionY() + 0.045) * scale); //bl
    glVertex2f((-0.19 + getPositionX()) * scale, (-0.20 + getPositionY() + 0.045) * scale);  //br
    glVertex2f((-0.1895 + getPositionX()) * scale, (-0.16 + getPositionY() + 0.045) * scale); //tr
    glVertex2f((-0.2375 + getPositionX()) * scale, (-0.16 + getPositionY() + 0.045) * scale); //tl
    glEnd();

    //rightLeg
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f((-0.0425 + getPositionX()) * scale, (-0.20 + getPositionY() + 0.045) * scale); //bl
    glVertex2f((0.0325 + getPositionX()) * scale, (-0.20 + getPositionY() + 0.045) * scale); //br
    glVertex2f((0.0325 + getPositionX()) * scale, (-0.10 + getPositionY() + 0.045) * scale); //tr
    glVertex2f((-0.0425 + getPositionX()) * scale, (-0.10 + getPositionY() + 0.045) * scale); //tl
    glEnd();

    //right foot
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f((-0.1025 + getPositionX()) * scale, (-0.20 + getPositionY() + 0.045) * scale); //bl
    glVertex2f((-0.005 + getPositionX()) * scale, (-0.20 + getPositionY() + 0.045) * scale);  //br
    glVertex2f((-0.025 + getPositionX()) * scale, (-0.16 + getPositionY() + 0.045) * scale); //tr
    glVertex2f((-0.08 + getPositionX()) * scale, (-0.16 + getPositionY() + 0.045) * scale); //tl
    glEnd();

    //eye
    glColor3f(1.0f, 0.361f, 0.361f);
    glBegin(GL_QUADS);
    glVertex2f((-0.1575 + getPositionX()) * scale, (0.0725 + getPositionY()) * scale); //bl
    glVertex2f((-0.0125 + getPositionX()) * scale, (0.0725 + getPositionY()) * scale); //br
    glVertex2f((-0.035 + getPositionX()) * scale, (0.115 + getPositionY()) * scale); //tr
    glVertex2f((-0.135 + getPositionX()) * scale, (0.115 + getPositionY()) * scale); //tl
    glEnd();
    glColor3f(1.0f, 0.361f, 0.361f);
    glBegin(GL_QUADS);
    glVertex2f((-0.035 + getPositionX()) * scale, (0.03 + getPositionY()) * scale); //bl
    glVertex2f((-0.135 + getPositionX()) * scale, (0.03 + getPositionY()) * scale); //br
    glVertex2f((-0.1575 + getPositionX()) * scale, (0.0725 + getPositionY()) * scale); //tr
    glVertex2f((-0.0125 + getPositionX()) * scale, (0.0725 + getPositionY()) * scale); //tl
    glEnd();

    //eye shine
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f((-0.0775 + getPositionX()) * scale, (0.095 + getPositionY()) * scale); //bl
    glVertex2f((-0.05 + getPositionX()) * scale, (0.0925 + getPositionY()) * scale); //br
    glVertex2f((-0.05 + getPositionX()) * scale, (0.1075 + getPositionY()) * scale); //tr
    glVertex2f((-0.0775 + getPositionX()) * scale, (0.1075 + getPositionY()) * scale); //tl
    glEnd();

    //eye shadow
    glColor3f(0.69f, 0.102f, 0.102f);
    glBegin(GL_QUADS);
    glVertex2f((-0.125 + getPositionX()) * scale, (0.045 + getPositionY()) * scale); //bl
    glVertex2f((-0.055 + getPositionX()) * scale, (0.045 + getPositionY()) * scale); //br
    glVertex2f((-0.03 + getPositionX()) * scale, (0.08 + getPositionY()) * scale); //tl
    glVertex2f((-0.0625 + getPositionX()) * scale, (0.0625 + getPositionY()) * scale); //tr
    glEnd();
}

void EnemyMongus::runOneFrame(){
    //Head
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f((-0.1975 + getPositionX()) * scale, (0.07755 + getPositionY()) * scale);   // Bottom-left vertex
    glVertex2f((0.0325 + getPositionX()) * scale, (0.0775+ getPositionY()) * scale);    // Bottom-right vertex
    glVertex2f((-0.0175 + getPositionX()) * scale, (0.15 + getPositionY()) * scale);     // Top-right vertex
    glVertex2f((-0.15 + getPositionX()) * scale, (0.15 + getPositionY()) * scale);    // Top-left vertex
    glEnd();

    //body
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f((-0.1975 + getPositionX()) * scale, (-0.10 + getPositionY()) * scale);   // Bottom-left vertex
    glVertex2f((0.0325 + getPositionX()) * scale, (-0.10+ getPositionY()) * scale);    // Bottom-right vertex
    glVertex2f((0.0325 + getPositionX()) * scale, (0.0775+ getPositionY()) * scale);    // Top-right vertex
    glVertex2f((-0.1975 + getPositionX()) * scale, (0.07755 + getPositionY()) * scale);   // Top-Left vertex
    glEnd();

    //Left foot back
    //left leg
    glColor3f(0.929, 0.929, 0.929);
    glBegin(GL_QUADS);
    glVertex2f((-0.21 + getPositionX()) * scale, (-0.1425 + getPositionY()) * scale);
    glVertex2f((-0.1175 + getPositionX()) * scale, (-0.1425 + getPositionY()) * scale);
    glVertex2f((-0.1275 + getPositionX()) * scale, (-0.10 + getPositionY()) * scale);
    glVertex2f((-0.1975 + getPositionX()) * scale, (-0.10 + getPositionY()) * scale);
    glEnd();

    //left foot bottomshadow
    glColor3f(0.859, 0.859, 0.859);
    glBegin(GL_QUADS);
    glVertex2f((-0.1975 + getPositionX()) * scale, (-0.155 + getPositionY()) * scale);
    glVertex2f((-0.13 + getPositionX()) * scale, (-0.155 + getPositionY()) * scale);
    glVertex2f((-0.1175 + getPositionX()) * scale, (-0.1425 + getPositionY()) * scale);
    glVertex2f((-0.21 + getPositionX()) * scale, (-0.1425 + getPositionY()) * scale);
    glEnd();

    //right foot topshadow
    glColor3f(0.859, 0.859, 0.859);
    glBegin(GL_QUADS);
    glVertex2f((-0.0675 + getPositionX()) * scale, (-0.0425 + getPositionY()) * scale); //bl
    glVertex2f((0.0475 + getPositionX()) * scale, (-0.0425 + getPositionY()) * scale); //br
    glVertex2f((0.0275 + getPositionX()) * scale, (-0.015 + getPositionY()) * scale); //tr
    glVertex2f((-0.0525 + getPositionX()) * scale, (-0.015 + getPositionY()) * scale); //tl
    glEnd();

    //rightFoot
    glColor3f(0.929, 0.929, 0.929);
    glBegin(GL_QUADS);
    glVertex2f((-0.0425 + getPositionX()) * scale, (-0.1425 + getPositionY()) * scale); //bl
    glVertex2f((0.0325 + getPositionX()) * scale, (-0.1425 + getPositionY()) * scale); //br
    glVertex2f((0.0475 + getPositionX()) * scale, (-0.0425 + getPositionY()) * scale); //tr
    glVertex2f((-0.0675 + getPositionX()) * scale, (-0.0425 + getPositionY()) * scale); //tl
    glEnd();

    //eye
    glColor3f(1.0f, 0.361f, 0.361f);
    glBegin(GL_QUADS);
    glVertex2f((-0.1575 + getPositionX()) * scale, (0.0725 + getPositionY()) * scale); //bl
    glVertex2f((-0.0125 + getPositionX()) * scale, (0.0725 + getPositionY()) * scale); //br
    glVertex2f((-0.035 + getPositionX()) * scale, (0.115 + getPositionY()) * scale); //tr
    glVertex2f((-0.135 + getPositionX()) * scale, (0.115 + getPositionY()) * scale); //tl
    glEnd();
    glColor3f(1.0f, 0.361f, 0.361f);
    glBegin(GL_QUADS);
    glVertex2f((-0.035 + getPositionX()) * scale, (0.03 + getPositionY()) * scale); //bl
    glVertex2f((-0.135 + getPositionX()) * scale, (0.03 + getPositionY()) * scale); //br
    glVertex2f((-0.1575 + getPositionX()) * scale, (0.0725 + getPositionY()) * scale); //tr
    glVertex2f((-0.0125 + getPositionX()) * scale, (0.0725 + getPositionY()) * scale); //tl
    glEnd();

    //eye shine
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f((-0.0775 + getPositionX()) * scale, (0.095 + getPositionY()) * scale); //bl
    glVertex2f((-0.05 + getPositionX()) * scale, (0.0925 + getPositionY()) * scale); //br
    glVertex2f((-0.05 + getPositionX()) * scale, (0.1075 + getPositionY()) * scale); //tr
    glVertex2f((-0.0775 + getPositionX()) * scale, (0.1075 + getPositionY()) * scale); //tl
    glEnd();

    //eye shadow
    glColor3f(0.69f, 0.102f, 0.102f);
    glBegin(GL_QUADS);
    glVertex2f((-0.125 + getPositionX()) * scale, (0.045 + getPositionY()) * scale); //bl
    glVertex2f((-0.055 + getPositionX()) * scale, (0.045 + getPositionY()) * scale); //br
    glVertex2f((-0.03 + getPositionX()) * scale, (0.08 + getPositionY()) * scale); //tl
    glVertex2f((-0.0625 + getPositionX()) * scale, (0.0625 + getPositionY()) * scale); //tr
    glEnd();
}


void EnemyMongus::runTwoFrame(){
    //Head
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f((-0.1975 + getPositionX()) * scale, (0.07755 + getPositionY()) * scale);   // Bottom-left vertex
    glVertex2f((0.0325 + getPositionX()) * scale, (0.0775+ getPositionY()) * scale);    // Bottom-right vertex
    glVertex2f((-0.0175 + getPositionX()) * scale, (0.15 + getPositionY()) * scale);     // Top-right vertex
    glVertex2f((-0.15 + getPositionX()) * scale, (0.15 + getPositionY()) * scale);    // Top-left vertex
    glEnd();

    //body
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f((-0.1975 + getPositionX()) * scale, (-0.10 + getPositionY()) * scale);   // Bottom-left vertex
    glVertex2f((0.0325 + getPositionX()) * scale, (-0.10+ getPositionY()) * scale);    // Bottom-right vertex
    glVertex2f((0.0325 + getPositionX()) * scale, (0.0775+ getPositionY()) * scale);    // Top-right vertex
    glVertex2f((-0.1975 + getPositionX()) * scale, (0.07755 + getPositionY()) * scale);   // Top-Left vertex
    glEnd();

    //Left foot back //im lazy so ill just move them by adding the values
    //left leg, Now the right leg
    glColor3f(0.929, 0.929, 0.929);
    glBegin(GL_QUADS);
    glVertex2f((-0.21 + getPositionX() + 0.16) * scale, (-0.1425 + getPositionY()) * scale);
    glVertex2f((-0.1175 + getPositionX() + 0.16) * scale, (-0.1425 + getPositionY()) * scale);
    glVertex2f((-0.1275 + getPositionX() + 0.16) * scale, (-0.10 + getPositionY()) * scale);
    glVertex2f((-0.1975 + getPositionX() + 0.16) * scale, (-0.10 + getPositionY()) * scale);
    glEnd();

    //left foot bottomshadow
    glColor3f(0.859, 0.859, 0.859);
    glBegin(GL_QUADS);
    glVertex2f((-0.1975 + getPositionX() + 0.16) * scale, (-0.155 + getPositionY()) * scale);
    glVertex2f((-0.13 + getPositionX() + 0.16) * scale, (-0.155 + getPositionY()) * scale);
    glVertex2f((-0.1175 + getPositionX() + 0.16) * scale, (-0.1425 + getPositionY()) * scale);
    glVertex2f((-0.21 + getPositionX() + 0.16) * scale, (-0.1425 + getPositionY()) * scale);
    glEnd();

    //right foot topshadow
    glColor3f(0.859, 0.859, 0.859);
    glBegin(GL_QUADS);
    glVertex2f((-0.0675 + getPositionX() - 0.16) * scale, (-0.0425 + getPositionY()) * scale); //bl
    glVertex2f((0.0475 + getPositionX()- 0.16) * scale, (-0.0425 + getPositionY()) * scale); //br
    glVertex2f((0.0275 + getPositionX()- 0.16) * scale, (-0.015 + getPositionY()) * scale); //tr
    glVertex2f((-0.0525 + getPositionX()- 0.16) * scale, (-0.015 + getPositionY()) * scale); //tl
    glEnd();

    //rightFoot
    glColor3f(0.929, 0.929, 0.929);
    glBegin(GL_QUADS);
    glVertex2f((-0.0425 + getPositionX()- 0.16) * scale, (-0.1425 + getPositionY()) * scale); //bl
    glVertex2f((0.0325 + getPositionX()- 0.16) * scale, (-0.1425 + getPositionY()) * scale); //br
    glVertex2f((0.0475 + getPositionX()- 0.16) * scale, (-0.0425 + getPositionY()) * scale); //tr
    glVertex2f((-0.0675 + getPositionX()- 0.16) * scale, (-0.0425 + getPositionY()) * scale); //tl
    glEnd();

    //eye
    glColor3f(1.0f, 0.361f, 0.361f);
    glBegin(GL_QUADS);
    glVertex2f((-0.1575 + getPositionX()) * scale, (0.0725 + getPositionY()) * scale); //bl
    glVertex2f((-0.0125 + getPositionX()) * scale, (0.0725 + getPositionY()) * scale); //br
    glVertex2f((-0.035 + getPositionX()) * scale, (0.115 + getPositionY()) * scale); //tr
    glVertex2f((-0.135 + getPositionX()) * scale, (0.115 + getPositionY()) * scale); //tl
    glEnd();
    glColor3f(1.0f, 0.361f, 0.361f);
    glBegin(GL_QUADS);
    glVertex2f((-0.035 + getPositionX()) * scale, (0.03 + getPositionY()) * scale); //bl
    glVertex2f((-0.135 + getPositionX()) * scale, (0.03 + getPositionY()) * scale); //br
    glVertex2f((-0.1575 + getPositionX()) * scale, (0.0725 + getPositionY()) * scale); //tr
    glVertex2f((-0.0125 + getPositionX()) * scale, (0.0725 + getPositionY()) * scale); //tl
    glEnd();

    //eye shine
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f((-0.0775 + getPositionX()) * scale, (0.095 + getPositionY()) * scale); //bl
    glVertex2f((-0.05 + getPositionX()) * scale, (0.0925 + getPositionY()) * scale); //br
    glVertex2f((-0.05 + getPositionX()) * scale, (0.1075 + getPositionY()) * scale); //tr
    glVertex2f((-0.0775 + getPositionX()) * scale, (0.1075 + getPositionY()) * scale); //tl
    glEnd();

    //eye shadow
    glColor3f(0.69f, 0.102f, 0.102f);
    glBegin(GL_QUADS);
    glVertex2f((-0.125 + getPositionX()) * scale, (0.045 + getPositionY()) * scale); //bl
    glVertex2f((-0.055 + getPositionX()) * scale, (0.045 + getPositionY()) * scale); //br
    glVertex2f((-0.03 + getPositionX()) * scale, (0.08 + getPositionY()) * scale); //tl
    glVertex2f((-0.0625 + getPositionX()) * scale, (0.0625 + getPositionY()) * scale); //tr
    glEnd();
}

