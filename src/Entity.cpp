//
// Created by Vanya Kootchin on 2021-11-10.
//

#include "Entity.h"
#include <iostream>

Entity::Entity(sf::Texture& texture, sf::Vector2f pos, float scale){
        this->sprite = sf::Sprite();
        this->sprite.setTexture(texture);
        float x_size = this->sprite.getTexture()->getSize().x;
        float y_size = this->sprite.getTexture()->getSize().y;
        this->sprite.setOrigin(0.5*x_size, 0.5*y_size);
        this->sprite.setPosition(sf::Vector2f(pos.x,pos.y));
        this->sprite.scale(sf::Vector2f(scale,scale));
}

sf::Sprite Entity::getSprite(){
    return this->sprite;
}

void Entity::setSpritePosition(sf::Vector2f position) {
    this->sprite.setPosition(position);
}

sf::Vector2f Entity::getSpritePosition() const {
    return sprite.getPosition();
}
