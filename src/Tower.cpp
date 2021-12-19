//
// Created by Vanya Kootchin on 2021-11-10.
//

#include "Tower.h"
#include <iostream>

Tower::Tower(sf::Texture& t, sf::Vector2f v, float s, int c, int delay, std::string projectileType) : Entity(t, v, s) {
    this->cost = c;
    this->fireDelayTime = delay;
    this->projectileType = projectileType;
}

void Tower::attack(sf::Vector2f targetPosition){
    std::cout << "Firing! @ : ( "<< targetPosition.x << ", " << targetPosition.y << " )" << std::endl;
}

int Tower::getCost(){
    return this->cost;
}

std::string Tower::getProjectileType() {
    return projectileType;
}



bool operator== (const Tower& t1, const Tower& t2) {
    return ((t1.range == t2.range) &&
            (t1.fireDelayTime == t2.fireDelayTime) &&
            (t1.cost == t2.cost) &&
            (t1.getSpritePosition() == t2.getSpritePosition())
    );
}

void Tower::setFireDelayTime(int delay) {
    fireDelayTime = delay;
}

void Tower::updateFireDelayTime() {
    fireDelayTime = fireDelayTime -1;
    if(fireDelayTime<0)
        fireDelayTime = 0;
}

int Tower::getFireDelayTime() {
    return fireDelayTime;
}