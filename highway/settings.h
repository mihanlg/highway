#ifndef SETTINGS_H
#define SETTINGS_H

#include <random>

class Highway;

class Settings
{
public:
    friend class Highway;
    Settings();
    //getters
    int getMinSpeed();
    int getMaxSpeed();
    double getRandomSpeed();
private:
    //setters
    void setMinSpeed(int speed);
    void setMaxSpeed(int speed);
private:
    std::default_random_engine generator;
    int minSpeed, maxSpeed;
};

#endif // SETTINGS_H
