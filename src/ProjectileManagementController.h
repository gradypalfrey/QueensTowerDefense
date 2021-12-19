//
// Created by Andrew Hayman on 2021-11-29.
//

#ifndef GGTOWERDEFENCE_PROJECTILEMANAGEMENTCONTROLLER_H
#define GGTOWERDEFENCE_PROJECTILEMANAGEMENTCONTROLLER_H

#include <vector>
#include "Projectile.h"

class ProjectileManagementController {
public:
    ProjectileManagementController();
    void addProjectile(Projectile projectile);
    void removeProjectile(Projectile& projectile);
    std::vector<Projectile> getProjectileSet();
    void renderAllProjectiles(sf::RenderWindow* gameScreen);
    void updateAllProjectilePositions();
private:
    std::vector<Projectile> projectileSet;
};

#endif //GGTOWERDEFENCE_PROJECTILEMANAGEMENTCONTROLLER_H
