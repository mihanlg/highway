#ifndef HIGHWAY_H
#define HIGHWAY_H

#include <memory>
#include <QObject>

#include "lane.h"
#include "settings.h"

#define maxLanes_ 10
#define updateTime_ 25

class Highway : public QObject
{
    Q_OBJECT
public:
    Highway(std::shared_ptr<Settings> settings);
    void scale(double dw);
    Lane* addLane();
    void deleteLane();
    void addRandomCar();
    void clean(); //removes cars from highway
    void checkTimers();
    void startUpdateTimer();
    void startAddRandomCarTimer();
    void stopAddRandomCarTimer();
    void setAddRandomCarTimerInterval(double interval);
    void destroy(); //deletes all lanes
    int getTotalNLanes();
    int getOpenedNLanes();
private slots:
    void updateLanes();
    void addRandomCarWithTimer();
private:
    std::shared_ptr<Settings> settings_;
    std::shared_ptr<QTimer> updateTimer_, addRandomCarTimer_;
    std::vector<std::shared_ptr<Lane>> lanes_;
};

#endif // HIGHWAY_H
