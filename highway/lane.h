#ifndef LANE_H
#define LANE_H

#include <QObject>
#include <QtWidgets>
#include <vector>
#include <memory>
#include <thread>
#include <chrono>

#include "car.h"
#include "laneview.h"
#include "settings.h"


class Lane : public QVBoxLayout
{
    Q_OBJECT
public:
    explicit Lane(std::shared_ptr<Settings> settings, QWidget *parent = 0, unsigned idLane = 0);
    ~Lane();
private:
    void startTimer();
signals:

public slots:
    void addCar();
    void moveCars();
private:
    std::shared_ptr<Settings> settings_;
    unsigned idLane_;
    std::shared_ptr<LaneView> laneView;
    std::shared_ptr<QHBoxLayout> buttonsLayout;
    std::shared_ptr<QPushButton> button;
    std::shared_ptr<QGraphicsScene> scene;
    std::shared_ptr<QTimer> timer;
    std::vector<std::shared_ptr<Car>> cars_;
};

#endif // LANE_H
