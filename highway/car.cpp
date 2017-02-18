#include "car.h"
#include <iostream>

Car::Car(std::shared_ptr<Settings> settings, QGraphicsItem *parent, qreal pos) :
    QGraphicsRectItem(baseCarX, -pos, baseCarWidth, baseCarLength, parent),
    settings_(settings)
{
    //std::cout << pos << std::endl;
    blueBrush = QBrush(Qt::blue);
    redBrush = QBrush(Qt::red);
    greenBrush = QBrush(Qt::green);
    setBrush(greenBrush);
    initSpeed_ = settings_->getRandomSpeed();
}


Car::~Car()
{

}

qreal Car::getPos() {
    return -pos().y();
}

qreal Car::getLength() {
    return rect().height();
}

void Car::moveBy(qreal dx, qreal dy) {
    QGraphicsRectItem::moveBy(dx, -dy);
}

void Car::move() {
    moveBy(0, initSpeed_);
}
