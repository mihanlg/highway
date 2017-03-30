#include "highway.h"


Highway::Highway(std::shared_ptr<Settings> settings) : settings_(settings) {
    updateTimer_ = std::make_shared<QTimer>();
    updateTimer_->setInterval(updateTime_);
    connect(updateTimer_.get(), SIGNAL(timeout()), this, SLOT(updateLanes()));
    updateTimer_->start();

    addRandomCarTimer_ = std::make_shared<QTimer>();
    connect(addRandomCarTimer_.get(), SIGNAL(timeout()), this, SLOT(addRandomCarWithTimer()));
}

Lane* Highway::addLane() {
    if (lanes_.size() && lanes_.back()->isClosed()) {
        lanes_.back()->open();
    }
    else if (lanes_.size() < maxLanes_) {
        std::weak_ptr<Lane> left;
        if (lanes_.size() > 0) left = lanes_.back();
        std::shared_ptr<Lane> newLane = std::make_shared<Lane>(settings_, left, nullptr, lanes_.size());
        if (lanes_.size() > 0)
            lanes_.back()->setRight(newLane);
        lanes_.push_back(newLane);
        return lanes_.back().get();
    }
    return nullptr;
}

void Highway::deleteLane() {
    if (lanes_.size() > 1) {
        if (lanes_.back()->isClosed()) {
            if (lanes_.back()->isEmptyLane()) {
                lanes_.pop_back();
            }
        } else lanes_.back()->close();
    }
}

void Highway::startUpdateTimer() {
    updateTimer_->start();
}

void Highway::startAddRandomCarTimer() {
    addRandomCarTimer_->start();
}

void Highway::stopAddRandomCarTimer() {
    addRandomCarTimer_->stop();
}

void Highway::setAddRandomCarTimerInterval(double interval) {
    addRandomCarTimer_->setInterval(interval);
}

void Highway::clear() {
    lanes_.clear();
}

int Highway::getSize() {
    return lanes_.size();
}

int Highway::getNLanes() {
    return lanes_.size() - lanes_.back()->isClosed();
}

void Highway::addRandomCarWithTimer() {
    addRandomCarTimer_->stop();
    addRandomCar();
    double t = settings_->getRandomAppearTime();
    addRandomCarTimer_->setInterval(t);
    addRandomCarTimer_->start();
}

void Highway::addRandomCar() {
    int max_l = lanes_.size();
    if (lanes_.back()->isClosed()) max_l--;
    int i = rand()%max_l;
    lanes_[i]->addCar();
}

void Highway::checkTimers() {
    if (settings_->isPaused()) {
        if (updateTimer_->isActive()) updateTimer_->stop();
        if (addRandomCarTimer_->isActive() && settings_->isAutoAppearOn()) {
            addRandomCarTimer_->setInterval(addRandomCarTimer_->remainingTime());
            addRandomCarTimer_->stop();
        }
    } else {
        if (!updateTimer_->isActive()) {
            updateTimer_->start();
        }
        if (settings_->isAutoAppearOn()) {
            if (!addRandomCarTimer_->isActive()) {
                addRandomCarTimer_->start();
            }
        }
    }
}

void Highway::updateLanes() {
    checkTimers();
    if (!lanes_.back()->isOpened()) {
        deleteLane();
    }
    for (auto lane: lanes_) {
        lane->updateCars();
    }
}

void Highway::clean() {
    for (auto lane: lanes_) {
        lane->clean();
    }
}

void Highway::scale(double dw) {
    if (settings_->getWidth() + dw < 10) return;
    settings_->updateWidth(dw);
    for (auto lane: lanes_) {
        lane->scale(dw);
    }
}
