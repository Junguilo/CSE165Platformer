#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
public:
    Entity();

private:
    //stats shared with all entities
    int health;
    int attack;
    float positionX;
    float positionY;

    float hitboxOne; //topLeft
    float hitboxTwo; //topRight
    float hitboxThree; //bottomLeft
    float hitboxFour; //bottomRight
};

#endif // ENTITY_H
