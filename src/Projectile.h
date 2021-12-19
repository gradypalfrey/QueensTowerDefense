//
// Created by Andrew Hayman on 2021-11-23.
//

#ifndef GGTOWERDEFENCE_PROJECTILE_H
#define GGTOWERDEFENCE_PROJECTILE_H

#include "Entity.h"
#include "Enemy.h"

class Projectile: public Entity {
private:
    sf::Vector2f velocity;
    int damage;
    float radius;
    float range;
public:
    Projectile(sf::Texture& texture, sf::Vector2f position, float scale, sf::Vector2f velocity, int damage, float radius, float range);
    bool Collision(Entity enemy);
    void incrementProjectilePosition();
    float getRange();
    friend bool operator== (const Projectile& p1, const Projectile& p2);
};

#endif //GGTOWERDEFENCE_PROJECTILE_H
