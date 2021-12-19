//
// Created by Andrew Hayman on 2021-11-16.
//

#ifndef GGTOWERDEFENCE_MAP_H
#define GGTOWERDEFENCE_MAP_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include "TextureManagement.h"

class Map {
private:
    std::vector<sf::Vector2f> path;      // Contains path for enemies to traverse according to top left tile position
    sf::Color pathColor;                 // Color of boxes for path
    sf::Color mainColor;                 // Color of the rest of the map
    sf::Vector2f mapSize;                // Dimension for map based on window size
    float squareSize;                    // Desired square size. Map size must be divisible by square size
public:
    Map(sf::Color pathColor=sf::Color(100, 250, 50),
        sf::Color mainColor=sf::Color(200, 150, 150),
        sf::Vector2f mapSize = sf::Vector2f(900.f, 1000.f),
        float squareSize = 40.f);
    void generateRandomPath();
    void renderMap(sf::RenderWindow* gameScreen);
    std::vector<sf::Vector2f> getPath();
    sf::Vector2f getNearestTile(sf::Vector2f);
    sf::Vector2f getNextPathPosition(sf::Vector2f);
    float getSquareSize();
    bool onPath(sf::Vector2f position);
    bool onGrid(sf::Vector2f position);

};

#endif //GGTOWERDEFENCE_MAP_H
