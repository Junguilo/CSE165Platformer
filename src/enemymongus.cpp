#include "enemymongus.h"

EnemyMongus::EnemyMongus() {
    qDebug() << "Enemy Created with No Stats";
}

EnemyMongus::EnemyMongus(int health, int attack, float positionX, float positionY){
    setHealth(health);
    setAttack(attack);
    setPosition(positionX, positionY);
    qDebug() << "Enemy Created with these Stats";
    qDebug() << "Health: " << getHealth();
    qDebug() << "Attack: " << getAttack();
    qDebug() << "PositionX: " << getPositionX();
    qDebug() << "PositionY: " << getPositionY();
    draw();
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

//With an animator(draw()), we can take these functions and make a switch statement
//in order to change the frame of the pictures.
//Switch statement? or Timer used in an if statement in order to animate.
//We will probably need to find a way to get the hitboxes of the entities.
void EnemyMongus::draw(){
    //will make this the animator,
    //all the frames will be drawn as functions.
    //idleFrame();
    //runOneFrame();
    //runTwoFrame();
}

void EnemyMongus::idleFrame(){
    //base x is L(-0.1975) & R(0.0325)
    //will swap later

    //----- Idle State ---
    //Head
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.1975 + getPositionX(), 0.07755 + getPositionY());   // Bottom-left vertex
    glVertex2f(0.0325 + getPositionX(), 0.0775+ getPositionY());    // Bottom-right vertex
    glVertex2f(-0.0175 + getPositionX(), 0.15 + getPositionY());     // Top-right vertex
    glVertex2f(-0.15 + getPositionX(), 0.15 + getPositionY());    // Top-left vertex
    glEnd();

    //body
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.1975 + getPositionX(), -0.10 + getPositionY());   // Bottom-left vertex
    glVertex2f(0.0325 + getPositionX(), -0.10+ getPositionY());    // Bottom-right vertex
    glVertex2f(0.0325 + getPositionX(), 0.0775+ getPositionY());    // Top-right vertex
    glVertex2f(-0.1975 + getPositionX(), 0.07755 + getPositionY());   // Top-Left vertex
    glEnd();

    //left leg
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.1975 + getPositionX(), -0.20 + getPositionY());
    glVertex2f(-0.1275 + getPositionX(), -0.20 + getPositionY());
    glVertex2f(-0.1275 + getPositionX(), -0.10 + getPositionY());
    glVertex2f(-0.1975 + getPositionX(), -0.10 + getPositionY());
    glEnd();

    //left foot
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.255 + getPositionX(), -0.20 + getPositionY()); //bl
    glVertex2f(-0.19 + getPositionX(), -0.20 + getPositionY());  //br
    glVertex2f(-0.1895 + getPositionX(), -0.16 + getPositionY()); //tr
    glVertex2f(-0.2375 + getPositionX(), -0.16 + getPositionY()); //tl
    glEnd();

    //rightLeg
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.0425 + getPositionX(), -0.20 + getPositionY()); //bl
    glVertex2f(0.0325 + getPositionX(), -0.20 + getPositionY()); //br
    glVertex2f(0.0325 + getPositionX(), -0.10 + getPositionY()); //tr
    glVertex2f(-0.0425 + getPositionX(), -0.10 + getPositionY()); //tl
    glEnd();

    //right foot
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.1025 + getPositionX(), -0.20 + getPositionY()); //bl
    glVertex2f(-0.005 + getPositionX(), -0.20 + getPositionY());  //br
    glVertex2f(-0.025 + getPositionX(), -0.16 + getPositionY()); //tr
    glVertex2f(-0.08 + getPositionX(), -0.16 + getPositionY()); //tl
    glEnd();

    //eye
    glColor3f(1.0f, 0.361f, 0.361f);
    glBegin(GL_QUADS);
    glVertex2f(-0.1575 + getPositionX(), 0.0725 + getPositionY()); //bl
    glVertex2f(-0.0125 + getPositionX(), 0.0725 + getPositionY()); //br
    glVertex2f(-0.035 + getPositionX(), 0.115 + getPositionY()); //tr
    glVertex2f(-0.135 + getPositionX(), 0.115 + getPositionY()); //tl
    glEnd();
    glColor3f(1.0f, 0.361f, 0.361f);
    glBegin(GL_QUADS);
    glVertex2f(-0.035 + getPositionX(), 0.03 + getPositionY()); //bl
    glVertex2f(-0.135 + getPositionX(), 0.03 + getPositionY()); //br
    glVertex2f(-0.1575 + getPositionX(), 0.0725 + getPositionY()); //tr
    glVertex2f(-0.0125 + getPositionX(), 0.0725 + getPositionY()); //tl
    glEnd();

    //eye shine
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.0775 + getPositionX(), 0.095 + getPositionY()); //bl
    glVertex2f(-0.05 + getPositionX(), 0.0925 + getPositionY()); //br
    glVertex2f(-0.05 + getPositionX(), 0.1075 + getPositionY()); //tr
    glVertex2f(-0.0775 + getPositionX(), 0.1075 + getPositionY()); //tl
    glEnd();

    //eye shadow
    glColor3f(0.69f, 0.102f, 0.102f);
    glBegin(GL_QUADS);
    glVertex2f(-0.125 + getPositionX(), 0.045 + getPositionY()); //bl
    glVertex2f(-0.055 + getPositionX(), 0.045 + getPositionY()); //br
    glVertex2f(-0.03 + getPositionX(), 0.08 + getPositionY()); //tl
    glVertex2f(-0.0625 + getPositionX(), 0.0625 + getPositionY()); //tr
    glEnd();
}

void EnemyMongus::runOneFrame(){
    //Head
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.1975 + getPositionX(), 0.07755 + getPositionY());   // Bottom-left vertex
    glVertex2f(0.0325 + getPositionX(), 0.0775+ getPositionY());    // Bottom-right vertex
    glVertex2f(-0.0175 + getPositionX(), 0.15 + getPositionY());     // Top-right vertex
    glVertex2f(-0.15 + getPositionX(), 0.15 + getPositionY());    // Top-left vertex
    glEnd();

    //body
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.1975 + getPositionX(), -0.10 + getPositionY());   // Bottom-left vertex
    glVertex2f(0.0325 + getPositionX(), -0.10+ getPositionY());    // Bottom-right vertex
    glVertex2f(0.0325 + getPositionX(), 0.0775+ getPositionY());    // Top-right vertex
    glVertex2f(-0.1975 + getPositionX(), 0.07755 + getPositionY());   // Top-Left vertex
    glEnd();

    //Left foot back
    //left leg
    glColor3f(0.929, 0.929, 0.929);
    glBegin(GL_QUADS);
    glVertex2f(-0.21 + getPositionX(), -0.1425 + getPositionY());
    glVertex2f(-0.1175 + getPositionX(), -0.1425 + getPositionY());
    glVertex2f(-0.1275 + getPositionX(), -0.10 + getPositionY());
    glVertex2f(-0.1975 + getPositionX(), -0.10 + getPositionY());
    glEnd();

    //left foot bottomshadow
    glColor3f(0.859, 0.859, 0.859);
    glBegin(GL_QUADS);
    glVertex2f(-0.1975 + getPositionX(), -0.155 + getPositionY());
    glVertex2f(-0.13 + getPositionX(), -0.155 + getPositionY());
    glVertex2f(-0.1175 + getPositionX(), -0.1425 + getPositionY());
    glVertex2f(-0.21 + getPositionX(), -0.1425 + getPositionY());
    glEnd();

    //right foot topshadow
    glColor3f(0.859, 0.859, 0.859);
    glBegin(GL_QUADS);
    glVertex2f(-0.0675 + getPositionX(), -0.0425 + getPositionY()); //bl
    glVertex2f(0.0475 + getPositionX(), -0.0425 + getPositionY()); //br
    glVertex2f(0.0275 + getPositionX(), -0.015 + getPositionY()); //tr
    glVertex2f(-0.0525 + getPositionX(), -0.015 + getPositionY()); //tl
    glEnd();


    //rightFoot
    glColor3f(0.929, 0.929, 0.929);
    glBegin(GL_QUADS);
    glVertex2f(-0.0425 + getPositionX(), -0.1425 + getPositionY()); //bl
    glVertex2f(0.0325 + getPositionX(), -0.1425 + getPositionY()); //br
    glVertex2f(0.0475 + getPositionX(), -0.0425 + getPositionY()); //tr
    glVertex2f(-0.0675 + getPositionX(), -0.0425 + getPositionY()); //tl
    glEnd();

    //eye
    glColor3f(1.0f, 0.361f, 0.361f);
    glBegin(GL_QUADS);
    glVertex2f(-0.1575 + getPositionX(), 0.0725 + getPositionY()); //bl
    glVertex2f(-0.0125 + getPositionX(), 0.0725 + getPositionY()); //br
    glVertex2f(-0.035 + getPositionX(), 0.115 + getPositionY()); //tr
    glVertex2f(-0.135 + getPositionX(), 0.115 + getPositionY()); //tl
    glEnd();
    glColor3f(1.0f, 0.361f, 0.361f);
    glBegin(GL_QUADS);
    glVertex2f(-0.035 + getPositionX(), 0.03 + getPositionY()); //bl
    glVertex2f(-0.135 + getPositionX(), 0.03 + getPositionY()); //br
    glVertex2f(-0.1575 + getPositionX(), 0.0725 + getPositionY()); //tr
    glVertex2f(-0.0125 + getPositionX(), 0.0725 + getPositionY()); //tl
    glEnd();

    //eye shine
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.0775 + getPositionX(), 0.095 + getPositionY()); //bl
    glVertex2f(-0.05 + getPositionX(), 0.0925 + getPositionY()); //br
    glVertex2f(-0.05 + getPositionX(), 0.1075 + getPositionY()); //tr
    glVertex2f(-0.0775 + getPositionX(), 0.1075 + getPositionY()); //tl
    glEnd();

    //eye shadow
    glColor3f(0.69f, 0.102f, 0.102f);
    glBegin(GL_QUADS);
    glVertex2f(-0.125 + getPositionX(), 0.045 + getPositionY()); //bl
    glVertex2f(-0.055 + getPositionX(), 0.045 + getPositionY()); //br
    glVertex2f(-0.03 + getPositionX(), 0.08 + getPositionY()); //tl
    glVertex2f(-0.0625 + getPositionX(), 0.0625 + getPositionY()); //tr
    glEnd();
}

void EnemyMongus::runTwoFrame(){
    //Head
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.1975 + getPositionX(), 0.07755 + getPositionY());   // Bottom-left vertex
    glVertex2f(0.0325 + getPositionX(), 0.0775+ getPositionY());    // Bottom-right vertex
    glVertex2f(-0.0175 + getPositionX(), 0.15 + getPositionY());     // Top-right vertex
    glVertex2f(-0.15 + getPositionX(), 0.15 + getPositionY());    // Top-left vertex
    glEnd();

    //body
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.1975 + getPositionX(), -0.10 + getPositionY());   // Bottom-left vertex
    glVertex2f(0.0325 + getPositionX(), -0.10+ getPositionY());    // Bottom-right vertex
    glVertex2f(0.0325 + getPositionX(), 0.0775+ getPositionY());    // Top-right vertex
    glVertex2f(-0.1975 + getPositionX(), 0.07755 + getPositionY());   // Top-Left vertex
    glEnd();

    //Left foot back //im lazy so ill just move them by adding the values
    //left leg, Now the right leg
    glColor3f(0.929, 0.929, 0.929);
    glBegin(GL_QUADS);
    glVertex2f(-0.21 + getPositionX() + 0.16, -0.1425 + getPositionY());
    glVertex2f(-0.1175 + getPositionX() + 0.16, -0.1425 + getPositionY());
    glVertex2f(-0.1275 + getPositionX() + 0.16, -0.10 + getPositionY());
    glVertex2f(-0.1975 + getPositionX() + 0.16, -0.10 + getPositionY());
    glEnd();

    //left foot bottomshadow
    glColor3f(0.859, 0.859, 0.859);
    glBegin(GL_QUADS);
    glVertex2f(-0.1975 + getPositionX()+ 0.16, -0.155 + getPositionY());
    glVertex2f(-0.13 + getPositionX()+ 0.16, -0.155 + getPositionY());
    glVertex2f(-0.1175 + getPositionX()+ 0.16, -0.1425 + getPositionY());
    glVertex2f(-0.21 + getPositionX()+ 0.16, -0.1425 + getPositionY());
    glEnd();

    //right foot topshadow
    glColor3f(0.859, 0.859, 0.859);
    glBegin(GL_QUADS);
    glVertex2f(-0.0675 + getPositionX() - 0.16, -0.0425 + getPositionY()); //bl
    glVertex2f(0.0475 + getPositionX()- 0.16, -0.0425 + getPositionY()); //br
    glVertex2f(0.0275 + getPositionX()- 0.16, -0.015 + getPositionY()); //tr
    glVertex2f(-0.0525 + getPositionX()- 0.16, -0.015 + getPositionY()); //tl
    glEnd();

    //rightFoot
    glColor3f(0.929, 0.929, 0.929);
    glBegin(GL_QUADS);
    glVertex2f(-0.0425 + getPositionX()- 0.16, -0.1425 + getPositionY()); //bl
    glVertex2f(0.0325 + getPositionX()- 0.16, -0.1425 + getPositionY()); //br
    glVertex2f(0.0475 + getPositionX()- 0.16, -0.0425 + getPositionY()); //tr
    glVertex2f(-0.0675 + getPositionX()- 0.16, -0.0425 + getPositionY()); //tl
    glEnd();

    //eye
    glColor3f(1.0f, 0.361f, 0.361f);
    glBegin(GL_QUADS);
    glVertex2f(-0.1575 + getPositionX(), 0.0725 + getPositionY()); //bl
    glVertex2f(-0.0125 + getPositionX(), 0.0725 + getPositionY()); //br
    glVertex2f(-0.035 + getPositionX(), 0.115 + getPositionY()); //tr
    glVertex2f(-0.135 + getPositionX(), 0.115 + getPositionY()); //tl
    glEnd();
    glColor3f(1.0f, 0.361f, 0.361f);
    glBegin(GL_QUADS);
    glVertex2f(-0.035 + getPositionX(), 0.03 + getPositionY()); //bl
    glVertex2f(-0.135 + getPositionX(), 0.03 + getPositionY()); //br
    glVertex2f(-0.1575 + getPositionX(), 0.0725 + getPositionY()); //tr
    glVertex2f(-0.0125 + getPositionX(), 0.0725 + getPositionY()); //tl
    glEnd();

    //eye shine
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.0775 + getPositionX(), 0.095 + getPositionY()); //bl
    glVertex2f(-0.05 + getPositionX(), 0.0925 + getPositionY()); //br
    glVertex2f(-0.05 + getPositionX(), 0.1075 + getPositionY()); //tr
    glVertex2f(-0.0775 + getPositionX(), 0.1075 + getPositionY()); //tl
    glEnd();

    //eye shadow
    glColor3f(0.69f, 0.102f, 0.102f);
    glBegin(GL_QUADS);
    glVertex2f(-0.125 + getPositionX(), 0.045 + getPositionY()); //bl
    glVertex2f(-0.055 + getPositionX(), 0.045 + getPositionY()); //br
    glVertex2f(-0.03 + getPositionX(), 0.08 + getPositionY()); //tl
    glVertex2f(-0.0625 + getPositionX(), 0.0625 + getPositionY()); //tr
    glEnd();
}
