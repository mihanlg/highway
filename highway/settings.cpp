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
    //std::cout << speed << std::endl;
    return speed;
}

double Settings::getMinAcceleration() {
    return minAcceleration;
}

double Settings::getMaxAcceleration() {
    return maxAcceleration;
}

double Settings::getMaxDeceleration() {
    return maxDeceleration;
}

double Settings::getRandomAppearTime() {
    double d = static_cast<double>(rand()%100)/100;
    return (minAppearTime + d*(maxAppearTime - minAppearTime))*1e3;
}

void Settings::setMinSpeed(int speed) {
    minSpeed = speed;
}

void Settings::setMaxSpeed(int speed) {
    maxSpeed = speed;
}

void Settings::setMinAcceleration(double speed) {
    minAcceleration = speed;
}

void Settings::setMaxAcceleration(double speed) {
    maxAcceleration = speed;
}

void Settings::setMaxDeceleration(double speed) {
    maxDeceleration = speed;
}

void Settings::setAutoAppear(bool state) {
    autoAppear = state;
}

void Settings::setMinAppearTime(double time) {
    minAppearTime = time;
}

void Settings::setMaxAppearTime(double time) {
    maxAppearTime = time;
}
