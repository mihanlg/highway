#include "lane.h"
#include <iostream>

Lane::Lane(QWidget *parent, unsigned idLane) :
    QVBoxLayout(parent),
    idLane_(idLane)
{
    scene = new QGraphicsScene();
    QBrush roadBrush = QBrush(QPixmap(":/images/road.jpg"));

    laneView = new QGraphicsView();
    laneView->setMinimumWidth(50);
    laneView->setMaximumWidth(50);
    laneView->setFrameShape(QFrame::NoFrame);
    laneView->setScene(scene);
    laneView->setBackgroundBrush(roadBrush);
    laneView->setCacheMode(QGraphicsView::CacheBackground);
    addWidget(laneView);

    button = new QPushButton();
    button->setText(tr("+"));
    button->setMinimumWidth(50);
    button->setMaximumWidth(50);
    buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(button);
    addLayout(buttonsLayout);

}

Lane::~Lane() {
    delete scene;
    delete button;
    delete buttonsLayout;
    delete laneView;
}
