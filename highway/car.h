#ifndef CAR_H
#define CAR_H

#include <QObject>
#include <QGraphicsItem>
#include <QBrush>
#include <memory>
#include <iostream>

#include "settings.h"

#define baseCarWidth 40
#define baseCarX -baseCarWidth/2
#define baseCarLength 60

class Car : public QGraphicsRectItem
{
    //Q_OBJECT
public:
    Car(std::shared_ptr<Settings> settings, QGraphicsItem * parent = 0, qreal pos = 0);
    ~Car();
    qreal getPos();
    qreal getLength();
    void move();
protected:
    void speedUp(double toSpeed);
    void speedDown(double toSpeed = 0);
    void moveBy(qreal dx, qreal dy);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
public:
    enum CarState {
        Broken,
        Working
    };
private:
    double initSpeed_, currentSpeed_;
    std::shared_ptr<Settings> settings_;
    int state_;
    QBrush redBrush_, greenBrush_, blueBrush_, yellowBrush_;
    std::shared_ptr<QGraphicsTextItem> speedText;

};

#endif // CAR_H
