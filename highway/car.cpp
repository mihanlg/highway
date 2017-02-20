#include "car.h"
#include <iomanip>
#include <sstream>

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

    speedText = std::make_shared<QGraphicsTextItem>();
    speedText->setPlainText("000.0");
    speedText->setPos(-speedText->boundingRect().width()/2, 0);
    speedText->setParentItem(this);
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
    double maxDelta = settings_->getMaxAcceleration();
    double minDelta = settings_->getMinAcceleration();
    double ds = std::min(maxDelta, std::max(minDelta, 0.2*fabs(initSpeed_ - currentSpeed_)));
    ds = std::min(ds, toSpeed - currentSpeed_);
    currentSpeed_ += ds;
}

void Car::speedDown(double toSpeed) {
    if (currentSpeed_ <= toSpeed) {
        if (state_ == Broken)
            setBrush(redBrush_);
        return;
    }
    setBrush(yellowBrush_);
    double maxDelta = settings_->getMaxDeceleration();
    double ds = std::min(maxDelta, currentSpeed_ - toSpeed);
    currentSpeed_ -= ds;
}

void Car::move() {
    if (state_ == Broken) speedDown();
    else if (currentSpeed_ < initSpeed_) speedUp(initSpeed_);
    else setBrush(greenBrush_);
    //std::string speed;
    //sprintf(&speed[0], "%f", currentSpeed_);
    char speed[10];
    sprintf(speed, "%.1f", currentSpeed_);
    //QString speed = std::to_string(currentSpeed_).c_str();
    speedText->setPlainText(speed);
    moveBy(0, currentSpeed_/20);
}

void Car::moveBy(qreal dx, qreal dy) {
    QGraphicsRectItem::moveBy(dx, -dy);
}
