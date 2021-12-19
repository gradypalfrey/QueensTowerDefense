//
// Created by grady on 2021-11-12.
//

#ifndef GGTOWERDEFENCE_ENEMY_H
#define GGTOWERDEFENCE_ENEMY_H

#include <vector>
#include "Entity.h"
using namespace std;

class Enemy: public Entity {
private:
    int health;
    int damage;
    sf::Vector2f velocity;
public:
    using Entity::Entity;
    Enemy(sf::Texture& texture, sf::Vector2f position, float scale, int health, int damage);
    void subractHealth(int damage);
    int getHealth();
    int getDamage();
    void incrementEnemyPosition(sf::Vector2f increment_vector, float speed, int squareSize);
    friend bool operator== (const Enemy& e1, const Enemy& e2);
};


#endif //GGTOWERDEFENCE_ENEMY_H
