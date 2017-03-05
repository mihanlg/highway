#include "lane.h"
#include <iostream>

//Lane::Lane(std::shared_ptr<Settings> settings, QWidget *parent, unsigned idLane) :
Lane::Lane(std::shared_ptr<Settings> &settings, std::weak_ptr<Lane> &left,
           QWidget *parent, unsigned idLane) :

    QVBoxLayout(parent),
    settings_(settings),
    left_(left),
    idLane_(idLane)
{
    scene_ = std::make_shared<QGraphicsScene>();
    QPixmap bg(":/images/road.jpg");
    QBrush roadBrush = QBrush(QPixmap(bg.scaledToWidth(baseLaneWidth)));

    laneView_ = std::make_shared<LaneView>();
    //laneView_->setMinimumWidth(baseLaneWidth);
    laneView_->setMaximumWidth(baseLaneWidth);
    laneView_->setMinimumHeight(minLaneHeight);

    laneView_->setFrameShape(QFrame::NoFrame);

    laneView_->setScene(scene_.get());
    laneView_->setBackgroundBrush(roadBrush);
    laneView_->setCacheMode(LaneView::CacheBackground);
    laneView_->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);

    laneView_->verticalScrollBar()->blockSignals(true);
    laneView_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    laneView_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    addWidget(laneView_.get());

    button_ = std::make_shared<QPushButton>();
    button_->setText(tr("+"));
    //button_->setMinimumWidth(baseLaneWidth);
    button_->setMaximumWidth(baseLaneWidth);
    connect(button_.get(), SIGNAL(clicked()), this, SLOT(addCar()));

    buttonsLayout_ = std::make_shared<QHBoxLayout>();
    buttonsLayout_->addWidget(button_.get());
    addLayout(buttonsLayout_.get());

    opened_ = true;
}

void Lane::setRight(std::weak_ptr<Lane> right) {
    right_ = right;
}


void Lane::addCar() {
    double maxCurrentSpeed = -1;
    if (cars_.size() == 0 ||
        (cars_.back()->getPos() > settings_->getMinDistance()*cars_.back()->getLength())) {
        if (cars_.size() != 0) {
            auto leadingCar = cars_.back();
            if (leadingCar->getPos() < settings_->getMaxDistance()*leadingCar->getLength())
                maxCurrentSpeed = cars_.back()->getReactionSpeed();
        }
        cars_.push_back(std::make_shared<Car>(settings_, maxCurrentSpeed, settings_->getCarID()));
        scene_->addItem(cars_.back().get());
    }
}

std::weak_ptr<Car> Lane::insertCar(std::shared_ptr<Car> &car) {
    std::weak_ptr<Car> leading;
    std::vector<std::shared_ptr<Car>>::iterator it;
    for (it = cars_.begin(); it < cars_.end(); it++) {
        if ((*it)->getPos() - (*it)->getLength() > car->getPos())
            leading = *it;
        else break;
    }
    it = cars_.insert(it, car);
    scene_->addItem(it->get());
    return leading;
}

std::weak_ptr<Car> Lane::getLeadingCarInLane(std::shared_ptr<Lane> lane, double pos) {
    std::shared_ptr<Car> leadingCar;
    for (auto iterCar: lane->cars_) {
        if (iterCar->getPos() > pos) leadingCar = iterCar;
        else break;
    }
    return leadingCar;
}

std::weak_ptr<Car> Lane::getFollowingCarInLane(std::shared_ptr<Lane> lane, double pos) {
    std::shared_ptr<Car> followingCar;
    for (auto iterCar: lane->cars_) {
        if (iterCar->getPos() > pos) continue;
        else {
            followingCar = iterCar;
            break;
        }
    }
    return followingCar;
}

bool Lane::checkLane(std::weak_ptr<Lane> lane, std::shared_ptr<Car> car) {
    std::shared_ptr<Lane> lane_;
    if ((lane_ = lane.lock())) {
        double carPos = car->getPos();
        double minDistance = car->getDangerousDistance();
        for (auto iterCar: lane_->cars_) {
            double iterCarPos = iterCar->getPos();
            if (fabs(iterCarPos - carPos) < minDistance) return false;
            if (iterCarPos < carPos) break;
        }
        return true;
    } else return false;
}

bool Lane::tryChangeLane(std::vector<std::shared_ptr<Car>>::iterator &car,
                         MoveDirection dir, double leadingSpeed) {
    std::weak_ptr<Lane> lane_ = dir == Left ? left_ : right_;
    if ((*car)->isBroken() ||
        ((*car)->isCrawling() && isOpened()) ||
        !checkLane(lane_, (*car)))
        return false;

    std::shared_ptr<Lane> lane = lane_.lock();
    if (lane->isClosed()) return false;

    std::shared_ptr<Car> leadingCar = getLeadingCarInLane(lane, (*car)->getPos()).lock();
    std::shared_ptr<Car> followingCar = getFollowingCarInLane(lane, (*car)->getPos()).lock();
    if (leadingCar) {
        double dist = fabs(leadingCar->getPos() - (*car)->getPos());
        if ((dist < (*car)->getDangerousDistance()) &&
                (leadingCar->getReactionSpeed() < (*car)->getRealSpeed()))
            return false;
        else if ((dist < (*car)->getBrakeDistance()) &&
                 (leadingCar->getReactionSpeed() < leadingSpeed))
            return false;
    }
    if (followingCar) {
        double dist = fabs((*car)->getPos() - followingCar->getPos());
        if ((dist < (*car)->getBrakeDistance()) &&
            ((*car)->getRealSpeed() < followingCar->getReactionSpeed())) {
            return false;
        }
    }
    //insert car
    leadingCar = lane->insertCar(*car).lock();
    if (dir == Left) {
        moveForward(*car);
    }
    //unfollow
    if (car != cars_.begin()) (*car)->unfollow(*(car-1));
    if (car != cars_.end()-1) (*(car+1))->unfollow(*car);
    //remove
    car = cars_.erase(car);
    return true;
}

void Lane::moveForward(std::shared_ptr<Car> car) {
    car->move();
}

void Lane::moveForward(std::shared_ptr<Car> car, std::shared_ptr<Car> leadingCar) {
    car->move(leadingCar);
}

void Lane::updateCars() {
    button_->setEnabled(isOpened());
    auto car = cars_.begin();
    while (car != cars_.end()) {
        (*car)->updateText();
        //clean
        if ((*car)->getPos() > laneView_->frameRect().height() + (*car)->getLength()) {
            if ((*car)->isFollowed()) (*(car+1))->unfollow(*car);
            car = cars_.erase(car);
            continue;
        }
        //move
        if (isClosed()) {
            if (tryChangeLane(car, Left, 0)) continue;
        }
        else if ((*car)->isFollowing()) {
            if (tryChangeLane(car, Left, (*(car-1))->getReactionSpeed()) ||
                tryChangeLane(car, Right, (*(car-1))->getReactionSpeed())) continue;
        }
        else if ((*car)->isFollowed()) {
                if (tryChangeLane(car, Right, 0)) continue;
        }
        if (car == cars_.begin()) moveForward(*car);
        else moveForward(*car, *(car-1));
        car++;
    }
    laneView_->update();
}

bool Lane::isOpened() {
    return opened_;
}

bool Lane::isClosed() {
    return !opened_;
}

bool Lane::isEmptyLane() {
    return !cars_.size();
}

void Lane::close() {
    opened_ = false;
}

void Lane::open() {
    opened_ = true;
}

void Lane::clean() {
    cars_.clear();
}

void Lane::scale(qreal s) {
    //setSizeConstraint();
    laneView_->scale(s, s);
    laneView_->resize(laneView_->width()*s, laneView_->height());
    /*button_->resize(button_->width()*s, button_->height());
    QRect but, lan;
    QRectF sc;
    but = buttonsLayout_->geometry();
    but.setWidth(but.width()*s);
    buttonsLayout_->setGeometry(but);
    lan = geometry();
    lan.setWidth(lan.width()*s);
    setGeometry(lan);
    sc = scene_->sceneRect();
    sc.setWidth(sc.width()*s);
    scene_->setSceneRect(sc);
    std::cout << "LV: " << laneView_->geometry().width() << std::endl;
    std::cout << "B: " << button_->geometry().width() << std::endl;
    std::cout << "BL: " << buttonsLayout_->geometry().width() << std::endl;
    std::cout << "Lane: " << geometry().width() << std::endl;*/
}

Lane::~Lane() {
}
