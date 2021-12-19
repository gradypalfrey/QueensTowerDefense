//
// Created by Andrew Hayman on 2021-11-22.
//

#include "TextureManagement.h"
#include <iostream>

TextureMap::TextureMap() {};

void TextureMap::insertTexture(std::string fileName, std::string textureName) {
    sf::Texture texture;
    if(!texture.loadFromFile(fileName)) {
        std::cerr << "ERROR: Could not open texture file: " << fileName << std::endl;
        throw std::exception();
    }
    textureMap.insert({textureName, texture});
}

sf::Texture& TextureMap::getTexture(std::string textureName) {
    return textureMap.find(textureName)->second;
}

