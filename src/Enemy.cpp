//
// Created by grady on 2021-11-12.
//

#include "Enemy.h"
#include <iostream>
Enemy::Enemy(sf::Texture& texture, sf::Vector2f position, float scale, int health, int damage):
    Entity(texture, position, scale),
    health(health),
    damage(damage) {
}

void Enemy::subractHealth(int damage) {
    health -= damage;
}

int Enemy::getHealth() {return health;}
int Enemy::getDamage() {return damage;}

void Enemy::incrementEnemyPosition(sf::Vector2f increment_vector, float speed, int squareSize) {
    float next_x = getSpritePosition().x + speed*increment_vector.x;
    float next_y = getSpritePosition().y + speed*increment_vector.y;
    if(increment_vector.x==0) {
        next_x = squareSize * (static_cast<int>(getSpritePosition().x) / squareSize)+squareSize/2;
    }
    if(increment_vector.y==0) {
        next_y = squareSize * (static_cast<int>(getSpritePosition().y) / squareSize)+squareSize/2;
    }
    setSpritePosition(sf::Vector2f(next_x, next_y));
}

bool operator== (const Enemy& e1, const Enemy& e2) {
    return ((e1.velocity == e2.velocity) &&
            (e1.health == e2.health) &&
            (e1.damage == e2.damage) &&
            (e1.getSpritePosition() == e2.getSpritePosition())
    );
}