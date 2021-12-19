//
// Created by Andrew Hayman on 2021-11-23.
//

#include "Projectile.h"
#include "Enemy.h"
#include <math.h>

Projectile::Projectile(sf::Texture& texture, sf::Vector2f position, float scale, sf::Vector2f velocity, int damage, float radius, float range) :
    Entity(texture, position, scale),
    velocity(velocity),
    damage(damage),
    radius(radius),
    range(range)
    {}

bool Projectile::Collision(Entity enemy) {
    float x_mag = (enemy.getSpritePosition().x-getSpritePosition().x)*(enemy.getSpritePosition().x-getSpritePosition().x);
    float y_mag = (enemy.getSpritePosition().y-getSpritePosition().y)*(enemy.getSpritePosition().y-getSpritePosition().y);
    float r_mag = radius*radius;
    return (x_mag+y_mag)<r_mag;
}

void Projectile::incrementProjectilePosition() {
    float x_next = getSpritePosition().x + velocity.x;
    float y_next = getSpritePosition().y + velocity.y;
    range -= sqrt(velocity.x*velocity.x+velocity.y*velocity.y);
    setSpritePosition(sf::Vector2f(x_next, y_next));
}

float Projectile::getRange() {
    return range;
}

bool operator== (const Projectile& p1, const Projectile& p2) {
    return ((p1.velocity == p2.velocity) &&
            (p1.radius == p2.radius) &&
            (p1.damage == p2.damage) &&
            (p1.getSpritePosition() == p2.getSpritePosition())
    );
}