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
    void scale(qreal s);
    Lane* addLane();
    void deleteLane();
    void addRandomCar();
    void clean();
    void checkTimers();
    void startUpdateTimer() {updateTimer_->start();}
    void startAddRandomCarTimer() {addRandomCarTimer_->start();}
    void stopAddRandomCarTimer() {addRandomCarTimer_->stop();}
    void setAddRandomCarTimerInterval(double interval) {addRandomCarTimer_->setInterval(interval);}
    void clear() {lanes_.clear();}
    int getSize() {return lanes_.size();}
    int getNLanes() {return lanes_.size() - lanes_.back()->isClosed();}
private slots:
    void updateLanes();
    void addRandomCarWithTimer();
private:
    std::shared_ptr<Settings> settings_;
    std::shared_ptr<QTimer> updateTimer_, addRandomCarTimer_;
    std::vector<std::shared_ptr<Lane>> lanes_;
};

#endif // HIGHWAY_H
