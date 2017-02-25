#include "lane.h"
#include <iostream>

Lane::Lane(std::shared_ptr<Settings> settings, QWidget *parent, unsigned idLane) :
    QVBoxLayout(parent),
    settings_(settings),
    idLane_(idLane)
{
    scene_ = std::make_shared<QGraphicsScene>();
    QBrush roadBrush = QBrush(QPixmap(":/images/road.jpg"));

    laneView_ = std::make_shared<LaneView>();
    laneView_->setMinimumWidth(baseLaneWidth);
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
    button_->setMinimumWidth(baseLaneWidth);
    button_->setMaximumWidth(baseLaneWidth);
    connect(button_.get(), SIGNAL(clicked()), this, SLOT(addCar()));

    buttonsLayout_ = std::make_shared<QHBoxLayout>();
    buttonsLayout_->addWidget(button_.get());
    addLayout(buttonsLayout_.get());

    opened_ = true;
}

void Lane::addCar() {
    if (cars_.size() == 0 || (cars_.back()->getPos() > settings_->getMinDistance()*cars_.back()->getLength())) {
        cars_.push_back(std::make_shared<Car>(settings_));
        scene_->addItem(cars_.back().get());
    }
}

void Lane::updateCars() {
    auto car = cars_.begin();
    while (car != cars_.end()) {
        if (car == cars_.begin()) (*car)->move();
        else (*car)->move(*(car-1));
        if ((*car)->getPos() > laneView_->frameRect().height() + (*car)->getLength()) {
            car = cars_.erase(car);
            (*car)->unfollow();
        } else car++;
    }
    laneView_->update();
}

bool Lane::isOpened() {
    return opened_;
}

Lane::~Lane() {
}
