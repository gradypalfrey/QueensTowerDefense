//
// Created by Andrew Hayman on 2021-11-30.
//

#ifndef GGTOWERDEFENCE_BANNER_H
#define GGTOWERDEFENCE_BANNER_H

#include <ostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Banner {
public:
    void init();
    void update(int health, int money, int level);
    void renderAll(sf::RenderWindow* gameScreen);
private:
    std::string bannerText;
    sf::Text banner;
    sf::Font font;
    sf::RectangleShape background;
    sf::RectangleShape background1;
};

#endif //GGTOWERDEFENCE_BANNER_H
