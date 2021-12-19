//
// Created by Vanya Kootchin on 2021-11-10.
//

#ifndef GGTOWERDEFENCE_ENTITY_H
#define GGTOWERDEFENCE_ENTITY_H

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

class Entity {
private:
    sf::Sprite sprite;
public:
    Entity() {};
    Entity(sf::Texture&, sf::Vector2f, float);
    sf::Sprite getSprite();
    void setSpritePosition(sf::Vector2f position);
    sf::Vector2f getSpritePosition() const;
};


#endif //GGTOWERDEFENCE_ENTITY_H
