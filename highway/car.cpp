#include "car.h"

Car::Car(std::shared_ptr<Settings> settings, double maxCurrentSpeed, unsigned carLength,
         int carID, qreal pos, QObject *parent_o, QGraphicsItem *parent) :
    QObject(parent_o),
    QGraphicsRectItem(baseCarX, pos+baseCarLength-carLength, baseCarWidth, carLength, parent),
    settings_(settings),
    carID_(carID)
{
    //QRectF r = rect();
    //unsigned newLength = settings_->getRandomCarLength();
    //r.setY(r.y() - (newHeight - r.height()));
    //r.setHeight(newLength);
    //setPos(getPos() - (newLength - getLength()));
    //setRect(r);
    speedingUpColor_ = QBrush(Qt::blue);
    brokenColor_ = QBrush(Qt::red);
    movingColor_ = QBrush(Qt::green);
    slowingDownColor_ = QBrush(Qt::yellow);
    followingColor_ = QBrush(Qt::darkGreen);
    crawlingColor_ = QBrush(Qt::magenta);
    setBrush(movingColor_);
    initSpeed_ = settings_->getRandomSpeed();
    currentSpeed_ = maxCurrentSpeed < 0 ? initSpeed_ : std::min(maxCurrentSpeed, initSpeed_);
    state_ = Moving;
    isFollowed_ = false;
    changeLineLimit_ = 0;

    speedText = std::make_shared<QGraphicsTextItem>();
    speedText->setPlainText("000.0");
    speedText->setRotation(-90.0);
    speedText->setParentItem(this);
    speedText->setPos(-speedText->boundingRect().height()/2, speedText->boundingRect().width()-2);

    for (unsigned i = 0; i < settings_->getReaction(); i++) speeds.push(currentSpeed_);

    brokenTimer_ = std::make_shared<QTimer>();
    connect(brokenTimer_.get(), SIGNAL(timeout()), this, SLOT(fix()));
}

int Car::getCarID() {
    return carID_;
}

double Car::getDangerousDistance() {
    return settings_->getMinDistance()*getLength();
}

double Car::getBrakeDistance() {
    return settings_->getMaxDistance()*getLength();
}

void Car::setChangeLineLimit(int limit) {
    changeLineLimit_ = limit;
}

int Car::getChangeLineLimit() {
    return changeLineLimit_;
}

void Car::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    if ((state_ == Broken) || (state_ == Crawling)) {
        fix();
    } else crawl();
}

void Car::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *)
{
    if (state_ != Broken) state_ = Broken;
}

qreal Car::getPos() {
    return pos().y();
}

qreal Car::getLength() {
    return rect().height();
}

double Car::getReactionSpeed() {
    return speeds.front();
}

double Car::getRealSpeed() {
    return currentSpeed_;
}

bool Car::isFollowed() {
    return isFollowed_;
}

bool Car::isFollowing() {
    return state_ == Following;
}

bool Car::isBroken() {
    return state_ == Broken;
}

bool Car::isCrawling() {
    return state_ == Crawling;
}

void Car::setSpeed(double toSpeed) {
    toSpeed = std::min(initSpeed_, toSpeed);
    double delta =  toSpeed - currentSpeed_;
    while (speeds.size() >= settings_->getReaction()) speeds.pop();
    speeds.push(currentSpeed_);
    if (state_ == Broken && fabs(currentSpeed_) <= eps) {
        setBrush(brokenColor_);
        currentSpeed_ = 0;
        return;
    }
    if (fabs(delta) <= eps) {
        if (state_ == Following) setBrush(followingColor_);
        else if (state_ == Crawling) setBrush(crawlingColor_);
        else setBrush(movingColor_);
        currentSpeed_ = toSpeed;
        return;
    }
    double ds = 0;
    if (delta < -eps) {
        setBrush(slowingDownColor_);
        double minDelta = -settings_->getMaxDeceleration();
        ds = std::max(minDelta, delta);
    }
    else if (delta > eps) {
        setBrush(speedingUpColor_);
        double maxDelta = settings_->getMaxAcceleration();
        double minDelta = settings_->getMinAcceleration();
        ds = std::min(maxDelta, std::max(minDelta, accelerationCoef*fabs(initSpeed_ - currentSpeed_)));
        ds = std::min(ds, delta);
    }
    currentSpeed_ += ds;
}

void Car::checkBrakeTimer() {
    if (settings_->isAutoFixOn()) {
        if (state_ == Moving || state_ == Following) brokenTimer_->stop();
        else {
            brokenTimer_->setInterval(settings_->getAutoFixTime()*1000);
            brokenTimer_->start();
        }
    } else brokenTimer_->stop();
}

void Car::brake(double meanSpeed) {
    state_ = Broken;
    currentSpeed_ = meanSpeed;
    checkBrakeTimer();
}

void Car::crawl() {
    state_ = Crawling;
    checkBrakeTimer();
}


void Car::fix() {
    state_ = Moving;
    checkBrakeTimer();
}

void Car::follow(std::shared_ptr<Car> toFollowCar) {
    state_ = Following;
    toFollowCar->isFollowed_ = true;
    qreal dist = toFollowCar->getPos() - toFollowCar->getLength() - getPos();
    qreal dangerousDist = getDangerousDistance();
    qreal brakeDist = getBrakeDistance();
    if (dist <= dangerousDist)
        followingSpeed_ = (dist/dangerousDist)*toFollowCar->getReactionSpeed();
    else if (dist <= brakeDist) {
        qreal coef =  (dist - dangerousDist)/(brakeDist - dangerousDist);
        followingSpeed_ = ((1-coef)*toFollowCar->getReactionSpeed() + coef*initSpeed_);
    } else unfollow(toFollowCar);
}

void Car::unfollow(std::shared_ptr<Car> leadingCar) {
    leadingCar->isFollowed_ = false;
    if (state_ == Following) state_ = Moving;
    followingSpeed_ = initSpeed_;
}



void Car::move() {
    if (changeLineLimit_) changeLineLimit_--;
    if (state_ == Broken) setSpeed(0);
    else if (state_ == Crawling) setSpeed(settings_->getCrawlingSpeed());
    else if (state_ == Following) setSpeed(followingSpeed_);
    else setSpeed(initSpeed_);
    updateText();
    moveBy(0, currentSpeed_/speedCoef);
}

void Car::move(std::shared_ptr<Car> leading) {
    if (state_ != Broken && state_ != Crawling) {
        qreal dist = leading->getPos() - leading->getLength() - getPos();
        qreal brakeDist = getBrakeDistance();
        if ((dist < brakeDist) && (leading->getReactionSpeed() < initSpeed_)) {
            follow(leading);
        }
        else if (isFollowing()) {
            unfollow(leading);
        }
    }
    move();
    if (getPos() > leading->getPos() - leading->getLength()) {
        double meanSpeed = (currentSpeed_ + leading->currentSpeed_) / 2;
        leading->setPos(getPos()+leading->getLength()+1);
        leading->brake(meanSpeed);
        brake(meanSpeed);
    }
}

void Car::setPos(qreal pos) {
    moveBy(0, pos - getPos());
}

void Car::updateText() {
    if (settings_->getShowSpeed() == showNothing) {
        speedText->hide();
    }
    else {
        char text[20];
        if (settings_->getShowSpeed() == showSpeed) {
            sprintf(text, "%.1f", currentSpeed_);
        }
        else if (settings_->getShowSpeed() == showNumber) {
            sprintf(text, "%d", carID_);
        }
        else if (settings_->getShowSpeed() == showStatus) {
            sprintf(text, "%d:%s%s", carID_, (isFollowing()? "F" : "N"), (isFollowed()? "F" : "N"));
        }
        else if (settings_->getShowSpeed() == showPosition) {
            sprintf(text, "%.0f:%.0f", getPos(), getPos()-getLength());

        }
        speedText->setPlainText(text);
        speedText->show();
    }
}
