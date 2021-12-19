#pragma once

#include "Entity.h"

class Nexus : public Entity{
public:
    Nexus() {};
    using Entity::Entity;
    Nexus(sf::Texture& t, sf::Vector2f v, float s, int h);
    int GetHealth();
    void SetHealth(int h);
    void removeHealth(int h);
    void renderNexus(sf::RenderWindow* gameScreen);
private:
    int NexusHealth;


};