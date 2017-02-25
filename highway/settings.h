#ifndef SETTINGS_H
#define SETTINGS_H

#include <random>

class Manipulator;

class Settings
{
public:
    friend class Manipulator;
    Settings();
    //getters
    int getMinSpeed();
    int getMaxSpeed();
    double getRandomSpeed();
    double getMinAcceleration();
    double getMaxAcceleration();
    double getMaxDeceleration();
    double getRandomAppearTime();
    double getMinDistance();
    double getMaxDistance();
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
    void setMinDistance(double distance);
    void setMaxDistance(double distance);
private:
    std::default_random_engine generator;
    int minSpeed, maxSpeed;
    double minAcceleration, maxAcceleration, maxDeceleration;
    bool autoAppear;
    double minAppearTime, maxAppearTime;
    double minDistance, maxDistance;
};

#endif // SETTINGS_H
