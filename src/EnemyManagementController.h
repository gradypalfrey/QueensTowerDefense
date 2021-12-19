//
// Created by grady on 2021-11-21.
//

#ifndef GGTOWERDEFENCE_ENEMYMANAGEMENTCONTROLLER_H
#define GGTOWERDEFENCE_ENEMYMANAGEMENTCONTROLLER_H

#include "Enemy.h"
#include "Map.h"
#include "Nexus.h"
#include "TextureManagement.h"
#include <vector>

class EnemyManagementController {
public:
    EnemyManagementController();
    std::vector<Enemy>& getEnemySet();
    void addEnemy(Enemy enemy);
    void releaseEnemy(Enemy enemy);
    void initializeWave(int level);
    void renderAllEnemies(sf::RenderWindow* gameScreen);
    void removeEnemy(Enemy& enemy);
    void updateAllEnemyPositions(Map& map, Nexus& nexus);
    void removeAllEnemies();
    int getNumEnemies();
private:
    std::vector<Enemy> enemySet;
    int num_enemies_in_queue;
    float spacing_time;
    float wave_spacing_time;
    int num_waves;
    int levelNum;
    clock_t startTimeEnemy;
    clock_t startTimeWave;
};


#endif //GGTOWERDEFENCE_ENEMYMANAGEMENTCONTROLLER_H
