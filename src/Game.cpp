//
// Created by grady on 2021-11-02.
//

#include "Game.h"
#include <iostream>
#include "Map.h"
#include "TowerManagementController.h"
#include "TextureManagement.h"
#include <math.h>
#include "Nexus.h"

void Game::initVariables() {
    this->window = nullptr;
}

void Game::initWindow(int w, int h, std::string win_name) {
    this->videoMode.width = w;
    this->videoMode.height = h;
    this->window = new sf::RenderWindow( sf::VideoMode( this->videoMode.width, this->videoMode.height ), win_name, sf::Style::Close );
    this->window->setFramerateLimit(60);
    level = 1;
    currentTowerTexture = "frosh";
}

void Game::initBanner() {
    banner = Banner();
    banner.init();
}

void Game::initMap() {
    map = Map();
    map.generateRandomPath();
}

void Game::initTowerManagementController() {
    towerController = TowerManagementController();
};

void Game::initProjectileManagementController() {
    projectileController = ProjectileManagementController();
};

void Game::initTimerController()    {
    timerController = TimerController();
}

void Game::initEnemyManagementController() {
    enemyController = EnemyManagementController();
}

void Game::initTextures()   {
    enemyTextures.insertTexture("../assets/sprites/Enemy Sprite 1.png", "enemy1");
    enemyTextures.insertTexture("../assets/sprites/Queen's Enemy Sprite Damage animation.png", "enemy1_damage");

    towerTextures.insertTexture("../assets/sprites/Frosh Sprite 3(1).png", "frosh");
    towerTextures.insertTexture("../assets/sprites/Frosh Action.png", "frosh_attack");
    towerTextures.insertTexture("../assets/sprites/Player Sprite 1 'Turbo Engineer'.png", "turbo");
    towerTextures.insertTexture("../assets/sprites/Player Sprite 1 'Turbo Engineer'.png", "turbo_attack");
    towerTextures.insertTexture("../assets/sprites/Player Sprite 2 'RItual Engineer'.png", "ritual");
    towerTextures.insertTexture("../assets/sprites/Player Sprite 2 'RItual Engineer' Action.png", "ritual_attack");

    projectileTextures.insertTexture("../assets/sprites/Turbo Pitcher.png", "pitcher");
    projectileTextures.insertTexture("../assets/sprites/Tam.png", "tam");
    projectileTextures.insertTexture("../assets/sprites/Ritual Bar.png", "ritual_bar");

    baseTexture.insertTexture("../assets/sprites/Grant Hall.png", "grant_hall");

    gameTextures.insertTexture("../assets/screens/Game Over Screen.png", "game_over");
    gameTextures.insertTexture("../assets/screens/Loading Screen v3.png", "loading");
    gameTextures.insertTexture("../assets/screens/Queen's TD Title v2 big gif.png", "main_menu");

    float ch_SCALE = 0.02;
}

void Game::initMoney(){
    money = Money(100);
}

Mode Game::getMode() {
    return mode;
}

Game::Game() {
    this->initVariables();
    this->initWindow(1000,1000, "Grizz0");
    this->initMap();
    this->initTowerManagementController();
    this->initTimerController();
    this->initProjectileManagementController();
    this->initTextures();
    this->initEnemyManagementController();
    this->initMoney();
    this->initBanner();
    nexus = Nexus(baseTexture.getTexture("grant_hall"), sf::Vector2f(map.getPath().back().x+120, map.getPath().back().y-80), 0.75, 1000);
    mode = menu;
}

Game::~Game() {
    delete this->window;
}

const bool Game::running() const {
    return this->window->isOpen();
}

void Game::pollEvents() {
    while (this->window->pollEvent(this->ev)) {
        switch (this->ev.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (ev.key.code == sf::Keyboard::Escape)
                    this->window->close();
                if(ev.key.code == sf::Keyboard::W) {
                    if (!isWave) {
                        isWave = true;
                        enemyController.initializeWave(level);
                    }
                }
                if(ev.key.code == sf::Keyboard::T) {
                    if (currentTowerTexture == "frosh") {
                        currentTowerTexture = "ritual";
                    } else if (currentTowerTexture == "ritual") {
                        currentTowerTexture = "turbo";
                    } else {
                        currentTowerTexture = "frosh";
                    }
                }
                if(ev.key.code == sf::Keyboard::P) {
                    mode = play;
                }
                break;
            case sf::Event::MouseButtonPressed:
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
                    cout << "X MOUSE: " << mouse_pos.x << " Y MOUSE: " << mouse_pos.y << endl;
                    if(dragging==true) {
                        sf::Vector2f tile_pos = map.getNearestTile(sf::Vector2f(mouse_pos));
                        Tower tower(towerTextures.getTexture(dragTowerType), tile_pos, 0.2, 20, 10, dragProjectileType);

                        if (
                                map.onGrid(tile_pos) &&
                                !map.onPath(tile_pos) &&
                                !towerController.towerOverlaps(tower) &&
                                (this->money.getAmount() - tower.getCost()) >= 0
                                ) {
                            towerController.addTower(tower);
                            this->money.setAmount(money.getAmount() - tower.getCost());
                        }
                        dragging = false;
                    }
                    else {
                        if(((mouse_pos.x-890-50)*(mouse_pos.x-890-50) +(mouse_pos.y-200-50)*(mouse_pos.y-200-50))<(50*50)) {
                            dragging = true;
                            dragTowerType = "frosh";
                            dragProjectileType = "tam";
                        }
                        if(((mouse_pos.x-890-50)*(mouse_pos.x-890-50) +(mouse_pos.y-400-50)*(mouse_pos.y-400-50))<(50*50)) {
                            dragging = true;
                            dragTowerType = "ritual";
                            dragProjectileType = "pitcher";
                        }
                        if(((mouse_pos.x-890-50)*(mouse_pos.x-890-50) +(mouse_pos.y-600-50)*(mouse_pos.y-600-50))<(50*50)) {
                            dragging = true;
                            dragTowerType = "turbo";
                            dragProjectileType = "ritual_bar";
                        }
                    }
                }
                break;
        }
    }
}


void Game::update() {
    this->pollEvents();

    // Launch Projectile Example. This should be eventually placed into its own function
    // where we loop over all towers and all enemies
    for(Tower& tower:towerController.getTowerSet()) {
        for(Enemy& enemy:enemyController.getEnemySet()) {
            if (tower.getFireDelayTime() == 0) {
                float x_vec = enemy.getSpritePosition().x - (tower.getSpritePosition().x);
                float y_vec = enemy.getSpritePosition().y - (tower.getSpritePosition().y);
                float distance = sqrt(x_vec * x_vec + y_vec * y_vec);
                float x_vel = x_vec / distance;
                float y_vel = y_vec/ distance;
                if (distance < 200) {
                    float x_tower_pos = tower.getSpritePosition().x;
                    float y_tower_pos = tower.getSpritePosition().y;
                    Projectile projectile(projectileTextures.getTexture(tower.getProjectileType()), sf::Vector2f(x_tower_pos, y_tower_pos), 0.05,
                                          sf::Vector2f(50 * x_vel, 50 * y_vel), 10, 40, 200);
                    projectileController.addProjectile(projectile);
                    tower.setFireDelayTime(50);
                }
            }
        }
        tower.updateFireDelayTime();
    }

    // Check for collisions Example. This should also be placed into its own function.
    for(Projectile& projectile:projectileController.getProjectileSet()) {
        for(Enemy& enemy:enemyController.getEnemySet()) {
            if (projectile.Collision(enemy)) {
                projectileController.removeProjectile(projectile);
                enemyController.removeEnemy(enemy);
                money.setAmount(money.getAmount() + 1);
                break;
            }
        }
    }

    // Check for level
    if(enemyController.getEnemySet().size()==0 && isWave && enemyController.getNumEnemies() == 0) {
        this->money.setAmount(money.getAmount() + level*20);
        level += 1;
        isWave = false;
    }

    // Update projectile positions
    projectileController.updateAllProjectilePositions();

    // Check for release
    Enemy enemy(enemyTextures.getTexture("enemy1"), sf::Vector2f(map.getPath()[0].x, map.getPath()[0].y), 0.1, 100, 100);
    enemyController.releaseEnemy(enemy);

    // Update enemy positions
    enemyController.updateAllEnemyPositions(map, nexus);

    // Check nexus health
    if(nexus.GetHealth()<=0) {
        enemyController.removeAllEnemies();
        towerController.removeAllTowers();
        for(Projectile& projectile:projectileController.getProjectileSet()) {
            projectileController.removeProjectile(projectile);
        }
        mode = gameover;
    }

    // Update banner
    banner.update(nexus.GetHealth(), money.getAmount(), level);

    // Update time
    timerController.time();
}

void Game::render()     {
    window->clear();

    map.renderMap(window);
    towerController.renderAllTowers(window);
    projectileController.renderAllProjectiles(window);
    enemyController.renderAllEnemies(window);
    nexus.renderNexus(window);
    banner.renderAll(window);
    renderTowerPanel();
    renderDraggedTower();

    if(nexus.GetHealth()<=0) {
        sf::Sprite gameOver;
        gameOver.setTexture(gameTextures.getTexture("game_over"));
        window->draw(gameOver);
    }

    this->window->display();
}

void Game::renderTowerPanel() {
    sf::Sprite froshTower;
    froshTower.setTexture(towerTextures.getTexture("frosh"));
    froshTower.setPosition(905,200);
    froshTower.setScale(0.3, 0.3);
    sf::CircleShape froshTowerBackground(50);
    froshTowerBackground.setPosition(890,200);
    froshTowerBackground.setFillColor(sf::Color(255, 255, 255, 80));
    froshTowerBackground.setOutlineThickness(2);
    froshTowerBackground.setOutlineColor(sf::Color::Yellow);
    window->draw(froshTowerBackground);
    window->draw(froshTower);

    sf::Sprite ritualTower;
    ritualTower.setTexture(towerTextures.getTexture("ritual"));
    ritualTower.setPosition(890,400);
    ritualTower.setScale(0.3, 0.3);
    sf::CircleShape ritualTowerBackground(50);
    ritualTowerBackground.setPosition(890,400);
    ritualTowerBackground.setOutlineThickness(2);
    ritualTowerBackground.setOutlineColor(sf::Color::Yellow);
    ritualTowerBackground.setFillColor(sf::Color(255, 255, 255, 80));
    window->draw(ritualTowerBackground);
    window->draw(ritualTower);

    sf::Sprite turboTower;
    turboTower.setTexture(towerTextures.getTexture("turbo"));
    turboTower.setPosition(895,600);
    turboTower.setScale(0.3, 0.3);
    sf::CircleShape turboTowerBackground(50);
    turboTowerBackground.setPosition(890,600);
    turboTowerBackground.setOutlineThickness(2);
    turboTowerBackground.setOutlineColor(sf::Color::Yellow);
    turboTowerBackground.setFillColor(sf::Color(255, 255, 255, 80));
    window->draw(turboTowerBackground);
    window->draw(turboTower);
}

void Game::renderDraggedTower() {
    if(dragging== true) {
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
        sf::Color rangeColor;

        sf::Vector2f tile_pos = map.getNearestTile(sf::Vector2f(mouse_pos));
        Tower tower(towerTextures.getTexture(dragTowerType), tile_pos, 0.2, 20, 10, dragProjectileType);

        if (
                map.onGrid(tile_pos) &&
                !map.onPath(tile_pos) &&
                !towerController.towerOverlaps(tower) &&
                (this->money.getAmount() - tower.getCost()) >= 0
                ) {
            rangeColor = sf::Color(255, 255, 255, 100);
        }
        else {
            rangeColor = sf::Color(255, 0, 0, 100);
        }

        sf::Sprite draggedTower;
        draggedTower.setScale(0.2, 0.2);
        draggedTower.setTexture(towerTextures.getTexture(dragTowerType));
        float x_size = draggedTower.getTexture()->getSize().x;
        float y_size = draggedTower.getTexture()->getSize().y;
        draggedTower.setOrigin(0.5*x_size, 0.5*y_size);
        draggedTower.setPosition(sf::Vector2f(mouse_pos));

        sf::CircleShape towerRange(200);
        towerRange.setPosition(sf::Vector2f(mouse_pos));
        towerRange.setFillColor(rangeColor);
        towerRange.setOrigin(sf::Vector2f(200,200));
        window->draw(towerRange);
        window->draw(draggedTower);
    }
}

void Game::gameMenu() {
    window->clear();
    sf::Sprite menu;
    menu.setTexture(gameTextures.getTexture("main_menu"));
    menu.setScale(3,3);
    window->draw(menu);
    this->window->display();
    level = 1;
    money = 100;
    isWave = false;
    nexus.SetHealth(1000);
    while (this->window->pollEvent(this->ev)) {
        if (ev.key.code == sf::Keyboard::P) {
            mode = play;
        }
    }
}

void Game::gameOver() {
    window->clear();
    sf::Sprite gameOver;
    gameOver.setTexture(gameTextures.getTexture("game_over"));
    window->draw(gameOver);
    this->window->display();
    level = 1;
    money = 100;
    isWave = false;
    nexus.SetHealth(1000);
    sf::sleep(sf::milliseconds(1500));
    mode = menu;
}