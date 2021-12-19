//
// Created by Vanya Kootchin on 2021-11-22.
//

#include "TimerController.h"

TimerController::TimerController() {
    this->clock = sf::Clock();
    this->framerate = 0;
    this->elapsed_time = 0;
}

void TimerController::time(){
    this->elapsed_time = this->clock.getElapsedTime().asSeconds();
    this->framerate    = 1.f/this->elapsed_time;
    this->clock.restart();
}

float TimerController::getFramerate() {
    return this->framerate;
}
float TimerController::getElapsedTime() {
    return this->elapsed_time;
}

std::string TimerController::log(){
    return "Framerate: " + std::to_string(this->framerate) + ", Elapsed Time: " + std::to_string(this->elapsed_time);
}