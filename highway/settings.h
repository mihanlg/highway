#ifndef SETTINGS_H
#define SETTINGS_H

#include <random>
#include <time.h>



class Manipulator;
class Car;

#define baseCarWidth 24
#define baseCarX -baseCarWidth/2
#define baseCarLength 40

#define baseLaneWidth 30
#define baseLaneX -baseLaneWidth/2
#define minLaneHeight 300

#define speedCoef 40
#define accelerationCoef 0.2

#define eps 1e-1

enum showInfo {
    showNothing,
    showSpeed,
    showNumber,
    showStatus,
    showPosition
};

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
    int getUniqueCarID();
    int getAutoFixTime();
    bool isAutoFixOn();
    bool isAutoAppearOn() { return autoAppear; }
    int getCrawlingSpeed();
    bool isPaused();
    void setPause(bool state);
    unsigned getReaction();
    unsigned getRandomCarLength();
    //GUI
    showInfo getShowSpeed();
    double getWidth();
    double getScale();
    void updateWidth(double dw);
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
    void setAutoFixTime(int time);
    void setAutoFixState(bool state);
    void setCrawlingSpeed(int speed);
    void setReaction(unsigned val);
    void setMinCarLength(unsigned val);
    void setMaxCarLength(unsigned val);
    //GUI
    void setShowSpeed(showInfo state);
private:
    std::mt19937 generator;
    bool paused;
    unsigned reaction;
    int lastCarID;
    int minSpeed, maxSpeed, crawlingSpeed;
    int autoFixTime;
    bool autoFixState;
    showInfo showSpeed;
    double minAcceleration, maxAcceleration, maxDeceleration;
    bool autoAppear;
    double minAppearTime, maxAppearTime;
    double minDistance, maxDistance;
    unsigned minCarLength, maxCarLength;
    double width, scale;
};

#endif // SETTINGS_H
