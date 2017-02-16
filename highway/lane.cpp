#include "lane.h"
#include <iostream>

Lane::Lane(QWidget *parent, unsigned idLane) :
    QVBoxLayout(parent),
    idLane_(idLane)
{
    std::string name = "laneLayout_" + std::to_string(idLane_);
    setObjectName(name.c_str());
    std::cout << name << std::endl;

    lineView = new QGraphicsView(parent);
    lineView->setMinimumWidth(50);
    lineView->setMaximumWidth(50);
    lineView->setFrameShape(QFrame::NoFrame);
    addWidget(lineView);
    buttonsLayout = new QHBoxLayout(parent);
    addLayout(buttonsLayout);
    button = new QPushButton(parent);
    button->setText(tr("+"));
    button->setMinimumWidth(50);
    button->setMaximumWidth(50);
    buttonsLayout->addWidget(button);

    scene = new QGraphicsScene(parent);
    QPixmap roadBG(":/images/road.jpg");
    QBrush roadBrush = QBrush(roadBG);

    lineView->setScene(scene);
    lineView->setBackgroundBrush(roadBrush);
    lineView->setCacheMode(QGraphicsView::CacheBackground);

}

Lane::~Lane() {
    delete scene;
    delete button;
    delete buttonsLayout;
    delete lineView;
}
