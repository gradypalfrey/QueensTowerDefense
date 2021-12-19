//
// Created by grady on 2021-11-21.
//

#include "EnemyManagementController.h"
#include <iostream>

EnemyManagementController::EnemyManagementController() {
    num_enemies_in_queue = 0;
}

void EnemyManagementController::addEnemy(Enemy enemy) {
    enemySet.push_back(enemy);
}

std::vector<Enemy>& EnemyManagementController::getEnemySet() {
    return enemySet;
}

int EnemyManagementController::getNumEnemies() {
    return num_enemies_in_queue;
}

void EnemyManagementController::removeEnemy(Enemy& enemy) {
    enemySet.erase(std::remove(enemySet.begin(), enemySet.end(), enemy), enemySet.end());
}

void EnemyManagementController::renderAllEnemies(sf::RenderWindow *gameScreen) {
    for(auto enemy:enemySet) {
        gameScreen->draw(enemy.getSprite());
    }
}

void EnemyManagementController::initializeWave(int level) {
    levelNum = level;
    num_waves = level-1;
    num_enemies_in_queue = levelNum * 10;
    spacing_time = 0.5 / ((float)level);
    wave_spacing_time = spacing_time*num_enemies_in_queue+0.5;
    std::cout << "spacing: " << spacing_time << std::endl;
    std::cout << "LEVEL: " << level << std::endl;
    startTimeEnemy = clock();
    startTimeWave = clock();
}

void EnemyManagementController::removeAllEnemies() {
    enemySet.clear();
    num_enemies_in_queue = 0;
    num_waves = 0;
}

void EnemyManagementController::releaseEnemy(Enemy enemy) {
    if (num_enemies_in_queue > 0) {
        double duration = (clock() - startTimeEnemy)/ (double) CLOCKS_PER_SEC; // / (double) CLOCKS_PER_SEC + ((double) rand() / (double) RAND_MAX);
        if (duration > spacing_time) {
            enemySet.push_back(enemy);
            num_enemies_in_queue -= 1;
            startTimeEnemy = clock();
        }
    }
    double waveDuration = (clock() - startTimeWave)/ (double) CLOCKS_PER_SEC;// / (double) CLOCKS_PER_SEC + ((double) rand() / (double) RAND_MAX);
    if(num_waves>0 && waveDuration > wave_spacing_time) {
        spacing_time *= 0.3;
        num_enemies_in_queue += (int)(levelNum * 5 * num_waves);
        wave_spacing_time = spacing_time*num_enemies_in_queue+0.5;
        num_waves -= 1;
        startTimeWave = clock();
    }
}

void EnemyManagementController::updateAllEnemyPositions(Map& map, Nexus& nexus) {
    for(Enemy& enemy:enemySet) {
        if(map.getNextPathPosition(enemy.getSpritePosition())==sf::Vector2f(map.getPath().back().x,map.getPath().back().y)) {
            nexus.removeHealth(enemy.getDamage());
            removeEnemy(enemy);
        }
        sf::Vector2f inc = map.getNextPathPosition(enemy.getSpritePosition()) - map.getNearestTile(enemy.getSpritePosition());

        enemy.incrementEnemyPosition(inc, 0.15, (int)map.getSquareSize());
    }
}