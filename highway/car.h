#ifndef CAR_H
#define CAR_H

#include <QObject>
#include <QGraphicsItem>
#include <QBrush>
#include <memory>

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
    void moveBy(qreal dx, qreal dy);
    void move();
private:
    double initSpeed_;
    std::shared_ptr<Settings> settings_;
    QBrush redBrush, greenBrush, blueBrush;
};

#endif // CAR_H
