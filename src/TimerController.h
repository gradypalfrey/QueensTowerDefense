//
// Created by Vanya Kootchin on 2021-11-22.
//

#ifndef GGTOWERDEFENCE_TIMERCONTROLLER_H
#define GGTOWERDEFENCE_TIMERCONTROLLER_H

#include <SFML/System.hpp>

class TimerController {
    private:
        sf::Clock clock;
        float framerate;
        float elapsed_time;

    public:
        TimerController();
        float getFramerate();
        float getElapsedTime();
        void time();
        std::string log();
};


#endif //GGTOWERDEFENCE_TIMERCONTROLLER_H
