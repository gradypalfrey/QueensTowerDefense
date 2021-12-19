//
// Created by Andrew Hayman on 2021-11-19.
//

#include "TowerManagementController.h"
#include <iostream>

TowerManagementController::TowerManagementController() {}

void TowerManagementController::addTower(Tower tower) {
    towerSet.push_back(tower);
}

void TowerManagementController::removeTower(Tower tower) {
    towerSet.erase(std::remove(towerSet.begin(), towerSet.end(), tower), towerSet.end());
}

std::vector<Tower>& TowerManagementController::getTowerSet() {
    return towerSet;
}

void TowerManagementController::renderAllTowers(sf::RenderWindow* gameScreen) {
    for(auto tower:towerSet) {
        gameScreen->draw(tower.getSprite());
    }
}

void TowerManagementController::removeAllTowers() {
    towerSet.clear();
}

bool TowerManagementController::towerOverlaps(Tower tower) {
    sf::Vector2f target_position = tower.getSpritePosition();
    if(std::find_if(towerSet.begin(), towerSet.end(), [&target_position](const Tower& input_tower) {return input_tower.getSpritePosition() == target_position;}) != towerSet.end())
        return true;
    else
        return false;
}