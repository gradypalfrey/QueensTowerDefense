//
// Created by Andrew Hayman on 2021-11-29.
//

#include "ProjectileManagementController.h"

ProjectileManagementController::ProjectileManagementController() {}

void ProjectileManagementController::addProjectile(Projectile projectile) {
    projectileSet.push_back(projectile);
}

void ProjectileManagementController::removeProjectile(Projectile& projectile) {
    projectileSet.erase(std::remove(projectileSet.begin(), projectileSet.end(), projectile), projectileSet.end());
}

std::vector<Projectile> ProjectileManagementController::getProjectileSet() {
    return projectileSet;
}

void ProjectileManagementController::renderAllProjectiles(sf::RenderWindow* gameScreen) {
    for(auto projectile:projectileSet) {
        gameScreen->draw(projectile.getSprite());
    }
}

void ProjectileManagementController::updateAllProjectilePositions() {
    for(Projectile& projectile:projectileSet) {
        projectile.incrementProjectilePosition();
        if(projectile.getRange()<=0) {
            removeProjectile(projectile);
        }
    }
}