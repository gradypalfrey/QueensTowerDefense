//
// Created by Andrew Hayman on 2021-11-22.
//

#ifndef GGTOWERDEFENCE_TEXTUREMANAGEMENT_H
#define GGTOWERDEFENCE_TEXTUREMANAGEMENT_H

#include <SFML/Graphics.hpp>

class TextureMap {
private:
    std::map <std::string, sf::Texture> textureMap;
public:
    TextureMap();
    void insertTexture(std::string fileName, std::string textureName);
    sf::Texture& getTexture(std::string textureName);
};

#endif //GGTOWERDEFENCE_TEXTUREMANAGEMENT_H
