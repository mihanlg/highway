#include "car.h"
#include <iomanip>
#include <sstream>

Car::Car(std::shared_ptr<Settings> settings, QObject *parent_o, QGraphicsItem *parent, qreal pos) :
    QObject(parent_o),
    QGraphicsRectItem(baseCarX, -pos, baseCarWidth, baseCarLength, parent),
    settings_(settings)
{
    blueBrush_ = QBrush(Qt::blue);
    redBrush_ = QBrush(Qt::red);
    greenBrush_ = QBrush(Qt::green);
    yellowBrush_ = QBrush(Qt::yellow);
    magentaBrush_ = QBrush(Qt::magenta);
    setBrush(greenBrush_);
    initSpeed_ = currentSpeed_ = settings_->getRandomSpeed();
    state_ = Moving;

    speedText = std::make_shared<QGraphicsTextItem>();
    speedText->setPlainText("000.0");
    speedText->setPos(-speedText->boundingRect().width()/2, 0);
    speedText->setParentItem(this);

    //brokenTimer_ = std::make_shared<QTimer>();
    //connect(brokenTimer_.get(), SIGNAL(timeout()), this, SLOT(fixMe()));
    //brokenTimer_->setInterval(5000);

}


Car::~Car()
{

}

void Car::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    state_ = state_ == Broken ? Moving : Broken;
}

qreal Car::getPos() {
    return -pos().y();
}

qreal Car::getLength() {
    return rect().height();
}

double Car::getSpeed() {
    return currentSpeed_;
}

/*void Car::speedUp(double toSpeed) {
    if (currentSpeed_ >= toSpeed) return;
    setBrush(blueBrush_);
    double maxDelta = settings_->getMaxAcceleration();
    double minDelta = settings_->getMinAcceleration();
    double ds = std::min(maxDelta, std::max(minDelta, 0.2*fabs(initSpeed_ - currentSpeed_)));
    ds = std::min(ds, toSpeed - currentSpeed_);
    currentSpeed_ += ds;
}

void Car::speedDown(double toSpeed) {
    if (state_ == Broken && currentSpeed_ <= toSpeed) { setBrush(redBrush_); return; }
    else if (state_ == Follwing && currentSpeed_ == toSpeed) { setBrush(orangeBrush_); }
    else setBrush(yellowBrush_);
    //if (currentSpeed <= toSpeed) return;
    double maxDelta = settings_->getMaxDeceleration();
    double ds = std::min(maxDelta, currentSpeed_ - toSpeed);
    currentSpeed_ -= ds;
}*/

void Car::setSpeed(double toSpeed) {
    double delta =  toSpeed - currentSpeed_;
    double ds = 0;
    if (state_ == Broken && currentSpeed_ == 0.0) { setBrush(redBrush_); return; }
    else if (state_ == Following && delta == 0) { setBrush(magentaBrush_); }
    if (delta < 0) {
        setBrush(yellowBrush_);
        double minDelta = -settings_->getMaxDeceleration();
        ds = std::max(minDelta, delta);
    }
    else if (delta > 0) {
        setBrush(blueBrush_);
        double maxDelta = settings_->getMaxAcceleration();
        double minDelta = settings_->getMinAcceleration();
        ds = std::min(maxDelta, std::max(minDelta, 0.2*fabs(initSpeed_ - currentSpeed_)));
        ds = std::min(ds, delta);
    }
    currentSpeed_ += ds;
}

void Car::brake(double meanSpeed) {
    state_ = Broken;
    currentSpeed_ = meanSpeed;
    //brokenTimer_->start();
}

void Car::fix() {
    state_ = Moving;
    //brokenTimer_->stop();
}

void Car::unfollow() {
    if (state_ == Following) state_ = Moving;
}

void Car::move() {
    if (state_ == Broken) setSpeed(0);
    else if (state_ == Following) setSpeed(followingSpeed_);
    else if (currentSpeed_ < initSpeed_) setSpeed(initSpeed_);
    else setBrush(greenBrush_);
    char speed[10];
    sprintf(speed, "%.1f", currentSpeed_);
    speedText->setPlainText(speed);
    moveBy(0, currentSpeed_/20);
}

void Car::move(std::shared_ptr<Car> leading) {
    if (state_ != Broken) {
        qreal lpos = leading->getPos();
        if (lpos - getPos() < settings_->getMaxDistance()*leading->getLength()) {
            if (((lpos - getPos()) > settings_->getMinDistance()*leading->getLength()) ||
                (followingSpeed_ > leading->getSpeed()))
                followingSpeed_ = leading->getSpeed();
            state_ = Following;
            setBrush(magentaBrush_);
        } else state_ = Moving;
    }
    move();
    if (getPos() > leading->getPos() - leading->getLength()) {
        double meanSpeed = (getSpeed() + leading->getSpeed()) / 2;
        leading->setPos(getPos()+leading->getLength()+1);
        brake(meanSpeed);
        leading->brake(meanSpeed);
    }
}

void Car::moveBy(qreal dx, qreal dy) {
    QGraphicsRectItem::moveBy(dx, -dy);
}

void Car::setPos(qreal pos) {
    qreal dy = pos - getPos();
    moveBy(0, dy);
}
