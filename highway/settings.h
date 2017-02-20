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
    double getMinAcceleration();
    double getMaxAcceleration();
    double getMaxDeceleration();
    double getRandomAppearTime();
private:
    //setters
    void setMinSpeed(int speed);
    void setMaxSpeed(int speed);
    void setMinAcceleration(double speed);
    void setMaxAcceleration(double speed);
    void setMaxDeceleration(double speed);
    void setAutoAppear(bool state);
    void setMinAppearTime(double time);
    void setMaxAppearTime(double time);
private:
    std::default_random_engine generator;
    int minSpeed, maxSpeed;
    double minAcceleration, maxAcceleration, maxDeceleration;
    bool autoAppear;
    double minAppearTime, maxAppearTime;
};

#endif // SETTINGS_H
