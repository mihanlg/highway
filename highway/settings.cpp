#include "settings.h"
#include <iostream>

Settings::Settings()
{

}

int Settings::getMinSpeed() {
    return minSpeed;
}

int Settings::getMaxSpeed() {
    return maxSpeed;
}

double Settings::getRandomSpeed() {
    double mean = (minSpeed + maxSpeed) / 2.0;
    double stddev = 2*sqrt(maxSpeed - minSpeed + 1e-8);
    std::normal_distribution<double> dist(mean, stddev);
    double speed = dist(generator);
    std::cout << speed << std::endl;
    return speed/50;
}

void Settings::setMinSpeed(int speed) {
    minSpeed = speed;
}

void Settings::setMaxSpeed(int speed) {
    maxSpeed = speed;
}
