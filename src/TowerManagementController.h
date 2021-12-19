//
// Created by Andrew Hayman on 2021-11-19.
//

#ifndef GGTOWERDEFENCE_TOWERMANAGEMENTCONTROLLER_H
#define GGTOWERDEFENCE_TOWERMANAGEMENTCONTROLLER_H

#include "Tower.h"
#include "Map.h"
#include <vector>

class TowerManagementController {
public:
    TowerManagementController();
    void addTower(Tower tower);
    void removeTower(Tower tower);
    std::vector<Tower>& getTowerSet();
    void removeAllTowers();
    void renderAllTowers(sf::RenderWindow* gameScreen);
    bool towerOverlaps(Tower tower);
private:
    std::vector<Tower> towerSet;
};
#endif //GGTOWERDEFENCE_TOWERMANAGEMENTCONTROLLER_H
