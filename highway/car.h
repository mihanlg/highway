#ifndef CAR_H
#define CAR_H

#include <QObject>
#include <QGraphicsItem>
#include <QBrush>
#include <QtWidgets>

#include <memory>
#include <iostream>

#include "settings.h"
//#include "manipulator.h"

#define baseCarWidth 40
#define baseCarX -baseCarWidth/2
#define baseCarLength 60


class Car : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Car(std::shared_ptr<Settings> settings, QObject *parent_o = 0, QGraphicsItem * parent = 0, qreal pos = 0);
    ~Car();
    qreal getPos();
    qreal getLength();
    double getSpeed();
    void brake(double meanSpeed);
    void fix();
    void unfollow();
    void move();
    void move(std::shared_ptr<Car> leading);
protected:
    //void speedUp(double toSpeed);
    //void speedDown(double toSpeed = 0);
    void setSpeed(double toSpeed);
    void moveBy(qreal dx, qreal dy);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    void setPos(qreal pos);
public:
    enum CarState {
        Broken,
        Following,
        Moving
    };
private:
    double initSpeed_, currentSpeed_, followingSpeed_;
    std::shared_ptr<Settings> settings_;
    int state_;
    //Manipulator *manipulator_;
    QBrush redBrush_, greenBrush_, blueBrush_, yellowBrush_, magentaBrush_;
    std::shared_ptr<QGraphicsTextItem> speedText;
    std::shared_ptr<QTimer> brokenTimer_;

};

#endif // CAR_H
