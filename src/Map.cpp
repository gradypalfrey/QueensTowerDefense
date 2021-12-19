//
// Created by Andrew Hayman on 2021-11-17.
//

#include "Map.h"
#include <vector>
#include <iostream>


Map::Map(sf::Color pathColor, sf::Color mainColor, sf::Vector2f inputMapSize, float squareSize) :
    pathColor(pathColor),
    mainColor(mainColor),
    squareSize(squareSize)
{
    mapSize.x = int(inputMapSize.x/squareSize)*squareSize;
    mapSize.y = int(inputMapSize.y/squareSize)*squareSize;
}

void Map::generateRandomPath() {
    int numCols = int(mapSize.x / squareSize);
    int numRows = int(mapSize.y / squareSize);
    int targetPathLength = 20;

    // The current path is fixed, but algorithms are being investigated for a random path generation.
    sf::Vector2f start(int(0.75*numCols)*squareSize, 0);
    path.push_back(start);

    sf::Vector2f current = start;
    sf::Vector2f next;
    for(int i=0; i<int(0.66*numRows); ++i) {
        next.x = current.x;
        next.y = current.y+squareSize;
        path.push_back(next);
        current = next;
    }
    for(int i=0; i<int(0.33*numCols); ++i) {
        next.x = current.x-squareSize;
        next.y = current.y;
        path.push_back(next);
        current = next;
    }
    for(int i=0; i<int(0.5*numRows); ++i) {
        next.x = current.x;
        next.y = current.y-squareSize;
        path.push_back(next);
        current = next;
    }
    for(int i=0; i<int(0.3*numCols); ++i) {
        next.x = current.x-squareSize;
        next.y = current.y;
        path.push_back(next);
        current = next;
    }
    for(int i=0; i<int(0.7*numRows); ++i) {
        next.x = current.x;
        next.y = current.y+squareSize;
        path.push_back(next);
        current = next;
    }
    while(next.x!=(numCols-4)*squareSize) {
        next.x = current.x+squareSize;
        next.y = current.y;
        path.push_back(next);
        current = next;
    }
    for(sf::Vector2f& tile:path) {
        tile.x += +squareSize/2;
        tile.y += +squareSize/2;
    }
}

void Map::renderMap(sf::RenderWindow* gameScreen) {
    int numRows = int(mapSize.x / squareSize);
    int numCols = int(mapSize.y / squareSize);
    sf::RectangleShape mainTile(sf::Vector2f(squareSize*numRows, squareSize*numCols));
    mainTile.setFillColor(mainColor);
//    gameScreen->draw(mainTile);
    TextureMap backgroud;
    backgroud.insertTexture("../assets/screens/background3.png", "background");

    sf::Sprite backgroundImage;
    backgroundImage.setTexture(backgroud.getTexture("background"));
    backgroundImage.setScale(2, 2);
    gameScreen->draw(backgroundImage);



    for(sf::Vector2f tile : path) {
        sf::RectangleShape mainTile(sf::Vector2f(squareSize, squareSize));
        mainTile.setOrigin(+squareSize/2, +squareSize/2);
        mainTile.setPosition(tile.x, tile.y);
        mainTile.setFillColor(sf::Color(255,255, 255, 128));
        mainTile.setOutlineColor(sf::Color(255,255, 255, 128));
        mainTile.setOutlineThickness(1.f);
        gameScreen->draw(mainTile);
    }

}

std::vector<sf::Vector2f> Map::getPath() {
    return path;
}

sf::Vector2f Map::getNearestTile(sf::Vector2f input_position) {
    float x = (int(input_position.x)/(int)squareSize)*(int)squareSize+squareSize/2;
    float y = (int(input_position.y)/(int)squareSize)*(int)squareSize+squareSize/2;
    return sf::Vector2f(x, y);
}

bool Map::onPath(sf::Vector2f position) {
    sf::Vector2f current_tile = getNearestTile(position);
    if(std::find(path.begin(), path.end(), current_tile) != path.end())
        return true;
    else
        return false;
}

bool Map::onGrid(sf::Vector2f position) {
    if(position.x<mapSize.x && position.y<mapSize.y)
        return true;
    else
        return false;
}

// This function is poorly written, and should possibly be placed in
// the enemy class, because it is only to update enemy position.
sf::Vector2f Map::getNextPathPosition(sf::Vector2f current_position) {
    sf::Vector2f current_tile = getNearestTile(current_position);
    auto item = find(path.begin(), path.end(), current_tile);
    if(item != path.end()) {
        int idx = item - path.begin() + 1;
        if(current_tile==path[idx])
            idx += 1;
        return path[idx];
    }
    else {
        return sf::Vector2f(-1,-1);
    }
}

float Map::getSquareSize() {
    return squareSize;
}