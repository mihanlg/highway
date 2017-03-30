#ifndef LANE_H
#define LANE_H

#include <QObject>
#include <QtWidgets>
#include <vector>
#include <memory>

#include "car.h"
#include "laneview.h"
#include "settings.h"

enum MoveDirection {
    Left,
    Right
};

class Lane : public QVBoxLayout
{
    Q_OBJECT
public:
    explicit Lane(std::shared_ptr<Settings> &settings, std::weak_ptr<Lane> &left, QWidget *parent = 0, unsigned idLane = 0);
    ~Lane();
public slots:
    void addCar(); 
public:
    void updateCars();
    bool isOpened();
    bool isClosed();
    bool isEmptyLane();
    void close();
    void open();
    void clean();
    void setRight(std::weak_ptr<Lane> right);
    void scale(double dw);
private:
    std::weak_ptr<Car> insertCar(std::shared_ptr<Car> &car);
    std::weak_ptr<Car> getLeadingCarInLane(std::shared_ptr<Lane> lane, double pos);
    std::weak_ptr<Car> getFollowingCarInLane(std::shared_ptr<Lane> lane, double pos);
    bool checkLane(std::weak_ptr<Lane> lane);
    void startTimer();
    bool tryChangeLane(std::vector<std::shared_ptr<Car>>::iterator &car, MoveDirection dir, double leadingSpeed = 0.0);
    //bool tryChangeLane(std::shared_ptr<Car> car, std::shared_ptr<Car> leadingCar, MoveDirection dir);
    //bool tryMoveLeft(std::shared_ptr<Car> car, std::shared_ptr<Car> leadingCar);
    void moveForward(std::shared_ptr<Car> car);
    void moveForward(std::shared_ptr<Car> car, std::shared_ptr<Car> leadingCar);
private:
    std::shared_ptr<Settings> settings_;
    std::weak_ptr<Lane> left_, right_;
    unsigned idLane_;
    bool opened_;
    std::shared_ptr<LaneView> laneView_;
    std::shared_ptr<QHBoxLayout> buttonsLayout_;
    std::shared_ptr<QPushButton> button_;
    std::shared_ptr<QGraphicsScene> scene_;
    std::shared_ptr<QTimer> timer_;
    std::vector<std::shared_ptr<Car>> cars_;
};

#endif // LANE_H
