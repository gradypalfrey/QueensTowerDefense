//
// Created by jjbon on 2021-11-21.
//

#include "Nexus.h"
#include <iostream>


int Nexus::GetHealth(){
    return NexusHealth;
}

void Nexus::SetHealth(int h){
    NexusHealth = h;
}

void Nexus::removeHealth(int h) {
    NexusHealth -= h;
}

Nexus::Nexus(sf::Texture& t, sf::Vector2f v, float s, int h) : Entity(t, v, s) {
    this->NexusHealth = h;
}

void Nexus::renderNexus(sf::RenderWindow* gameScreen) {
    gameScreen->draw(getSprite());
}
