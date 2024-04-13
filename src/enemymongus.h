#ifndef ENEMYMONGUS_H
#define ENEMYMONGUS_H
#include "entity.h"


class EnemyMongus: public Entity
{
public:
    EnemyMongus();
    EnemyMongus(int health, int attack, float positionX, float positionY);
    void draw();

    //maybe we need these??
    int getEnemyHealth() const;
    int getEnemyAttack() const;
    float getEnemyPositionX() const;
    float getEnemyPositionY() const;
private:
    void idleFrame();
    void runOneFrame();
    void runTwoFrame();
};

#endif // ENEMYMONGUS_H
