//
// Created by grady on 2021-11-02.
//

#ifndef GGTOWERDEFENCE_GAME_H
#define GGTOWERDEFENCE_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <map>

#include "Entity.h"
#include "Map.h"
#include "Tower.h"
#include "TowerManagementController.h"
#include "ProjectileManagementController.h"
#include "TimerController.h"
#include "TextureManagement.h"
#include "EnemyManagementController.h"
#include "Money.h"
#include "Banner.h"
#include "Nexus.h"

enum Mode {menu, play, gameover};

class Game {
private:
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;
    Map map;
    TowerManagementController towerController;
    TimerController           timerController;
    ProjectileManagementController projectileController;
    EnemyManagementController enemyController;
    TextureMap gameTextures;
    TextureMap towerTextures;
    TextureMap enemyTextures;
    TextureMap baseTexture;
    TextureMap projectileTextures;
    TextureMap screens;
    Money money;
    Nexus nexus;
    Banner banner;
    int level;
    bool isWave;
    Mode mode;
    bool dragging;
    string dragTowerType;
    string dragProjectileType;

    void initBanner();
    void initVariables();
    void initWindow(int, int, std::string);
    void initMap();
    void initTowerManagementController();
    void initEnemyManagementController();
    void initProjectileManagementController();
    void initTimerController();
    void initTextures();
    void initMoney();
    void renderTowerPanel();
    void renderDraggedTower();

    string currentTowerTexture;

public:
    //Constructors
    Game();
    virtual ~Game();

    const bool running() const;

    //Functions
    void pollEvents();
    void update();
    void render();
    Mode getMode();
    void gameOver();
    void gameMenu();
};


#endif //GGTOWERDEFENCE_GAME_H
