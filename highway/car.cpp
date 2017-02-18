#include "car.h"
//#include <iostream>

Car::Car(std::shared_ptr<Settings> settings, QGraphicsItem *parent, qreal pos) :
    QGraphicsRectItem(baseCarX, -pos, baseCarWidth, baseCarLength, parent),
    settings_(settings)
{
    blueBrush_ = QBrush(Qt::blue);
    redBrush_ = QBrush(Qt::red);
    greenBrush_ = QBrush(Qt::green);
    yellowBrush_ = QBrush(Qt::yellow);
    setBrush(greenBrush_);
    initSpeed_ = currentSpeed_ = settings_->getRandomSpeed();
    state_ = Working;
}


Car::~Car()
{

}

void Car::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    state_ = state_ == Working ? Broken : Working;
}

qreal Car::getPos() {
    return -pos().y();
}

qreal Car::getLength() {
    return rect().height();
}

void Car::speedUp(double toSpeed) {
    if (currentSpeed_ >= toSpeed) return;
    setBrush(blueBrush_);
    double maxDelta = std::min(3.0, std::max(0.5, 0.2*fabs(initSpeed_ - currentSpeed_)));
    double ds = std::min(maxDelta, toSpeed - currentSpeed_);
    currentSpeed_ += ds;
}

void Car::speedDown(double toSpeed) {
    if (currentSpeed_ <= toSpeed) {
        if (state_ == Broken)
            setBrush(redBrush_);
        return;
    }
    setBrush(yellowBrush_);
    double maxDelta = 1.0;
    double ds = std::min(maxDelta, currentSpeed_ - toSpeed);
    currentSpeed_ -= ds;
}

void Car::move() {
    if (state_ == Broken) speedDown();
    else if (currentSpeed_ < initSpeed_) speedUp(initSpeed_);
    else setBrush(greenBrush_);
    moveBy(0, currentSpeed_/20);
}

void Car::moveBy(qreal dx, qreal dy) {
    QGraphicsRectItem::moveBy(dx, -dy);
}
