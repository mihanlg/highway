#include "lane.h"
#include <iostream>

Lane::Lane(std::shared_ptr<Settings> settings, QWidget *parent, unsigned idLane) :
    QVBoxLayout(parent),
    settings_(settings),
    idLane_(idLane)
{
    scene = std::make_shared<QGraphicsScene>();
    QBrush roadBrush = QBrush(QPixmap(":/images/road.jpg"));

    laneView = std::make_shared<LaneView>();
    laneView->setMinimumWidth(baseLaneWidth);
    laneView->setMaximumWidth(baseLaneWidth);
    laneView->setMinimumHeight(minLaneHeight);

    laneView->setFrameShape(QFrame::NoFrame);

    laneView->setScene(scene.get());
    laneView->setBackgroundBrush(roadBrush);
    laneView->setCacheMode(LaneView::CacheBackground);
    laneView->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);

    laneView->verticalScrollBar()->blockSignals(true);
    laneView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    laneView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    addWidget(laneView.get());

    button = std::make_shared<QPushButton>();
    button->setText(tr("+"));
    button->setMinimumWidth(baseLaneWidth);
    button->setMaximumWidth(baseLaneWidth);
    connect(button.get(), SIGNAL(clicked()), this, SLOT(addCar()));

    buttonsLayout = std::make_shared<QHBoxLayout>();
    buttonsLayout->addWidget(button.get());
    addLayout(buttonsLayout.get());

    timer = std::make_shared<QTimer>();
    timer->setInterval(40);
    connect(timer.get(), SIGNAL(timeout()), this, SLOT(moveCars()));
    timer->start();
}

void Lane::moveCars() {
    auto car = cars_.begin();
    while (car != cars_.end()) {
        (*car)->move();
        if ((*car)->getPos() > laneView->frameRect().height() + (*car)->getLength()) {
            car = cars_.erase(car);
        } else car++;
    }
    laneView->update();
}

void Lane::addCar() {
    cars_.push_back(std::make_shared<Car>(settings_));
    scene->addItem(cars_.back().get());
}

Lane::~Lane() {
}
