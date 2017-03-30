#ifndef CAR_H
#define CAR_H

#include <QObject>
#include <QGraphicsItem>
#include <QBrush>
#include <QtWidgets>

#include <memory>
#include <iostream>
#include <iomanip>
#include <sstream>

#include <queue>

#include "settings.h"



class Car : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Car(std::shared_ptr<Settings> settings,  double maxCurrentSpeed, unsigned carLength,
        int carID, qreal pos = 0, QObject *parent_o = 0, QGraphicsItem * parent = 0);
    qreal getPos();
    qreal getLength();
    double getReactionSpeed();
    double getRealSpeed();
    double getDangerousDistance();
    double getBrakeDistance();
    void setChangeLineLimit(int limit);
    int getChangeLineLimit();
    void checkBrakeTimer();
    void brake(double meanSpeed);
    void crawl();
    void follow(std::shared_ptr<Car> toFollowCar);
    void unfollow(std::shared_ptr<Car> leadingCar);
    void move();
    void move(std::shared_ptr<Car> leading);
    bool isFollowed();
    bool isFollowing();
    bool isBroken();
    bool isCrawling();
    int getCarID();
    void updateText();
protected:
    void setSpeed(double toSpeed);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
public slots:
    void fix();
private:
    void setPos(qreal pos);
public:
    enum CarState {
        Broken,
        Following,
        Moving,
        Crawling
    };
private:
    double initSpeed_, currentSpeed_, followingSpeed_;
    std::shared_ptr<Settings> settings_;
    int carID_;
    int state_;
    std::queue<double> speeds;
    bool isFollowed_;
    int changeLineLimit_;
    QBrush brokenColor_, movingColor_, speedingUpColor_, slowingDownColor_, followingColor_, crawlingColor_;
    std::shared_ptr<QGraphicsTextItem> speedText;
    std::shared_ptr<QTimer> brokenTimer_;

};

#endif // CAR_H
