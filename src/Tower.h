//
// Created by Vanya Kootchin on 2021-11-10.
//

#ifndef GGTOWERDEFENCE_TOWER_H
#define GGTOWERDEFENCE_TOWER_H

#include "Entity.h"

class Tower: public Entity {
private:
    std::string projectileType;
    double range;
    int fireDelayTime;
    int cost;
public:
    using Entity::Entity; // Use the entity constructor
    Tower(sf::Texture&, sf::Vector2f, float, int, int, std::string);
    void attack(sf:: Vector2f);
    int getCost();
    int getFireDelayTime();
    std::string getProjectileType();
    void updateFireDelayTime();
    void setFireDelayTime(int delay);
    friend bool operator== (const Tower& t1, const Tower& t2);
};


#endif //GGTOWERDEFENCE_TOWER_H
