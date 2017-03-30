#include "settings.h"
#include <iostream>

Settings::Settings() {
    srand(time(NULL));
    std::random_device rd;
    generator = std::mt19937(rd());
    lastCarID = -1;
}

//GETTERS

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


double Settings::getMinDistance() {
    return minDistance;
}

double Settings::getMaxDistance() {
    return maxDistance;
}

int Settings::getAutoFixTime() {
    return autoFixTime;
}

bool Settings::isAutoFixOn() {
    return autoFixState;
}

int Settings::getCarID() {
    return ++lastCarID;
}

int Settings::getCrawlingSpeed() {
    return crawlingSpeed;
}

showInfo Settings::getShowSpeed() {
    return showSpeed;
}

bool Settings::isPaused() {
    return paused;
}

unsigned Settings::getReaction() {
    return reaction;
}

unsigned Settings::getRandomCarLength() {
    return minCarLength + rand()%(maxCarLength - minCarLength + 1);
}

//SETTERS
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


void Settings::setMinDistance(double distance) {
    minDistance = distance;
}

void Settings::setMaxDistance(double distance) {
    maxDistance = distance;
}

void Settings::setAutoFixTime(int time) {
    autoFixTime = time;
}

void Settings::setAutoFixState(bool state) {
    autoFixState = state;
}

void Settings::setCrawlingSpeed(int speed) {
    crawlingSpeed = speed;
}

void Settings::setShowSpeed(showInfo state) {
    showSpeed = state;
}

void Settings::setPause(bool state) {
    paused = state;
}

void Settings::setReaction(unsigned val) {
    reaction = val;
}

void Settings::setMinCarLength(unsigned val) {
    minCarLength = val;
}

void Settings::setMaxCarLength(unsigned val) {
    maxCarLength = val;
}
