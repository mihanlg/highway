#include "highwaywindow.h"
#include "ui_highwaywindow.h"
#include <iostream>


HighwayWindow::HighwayWindow(QWidget *parent, unsigned nLanes) :
    QMainWindow(parent),
    ui(new Ui::HighwayWindow),
    nLanes_(nLanes)
{
    ui->setupUi(this);

    //rectangle = scene->addRect(0, 0, 40, 60, outlinePen, greenBrush);
    //ui->lineView->backgroundBrush();
    //rectangle->setFlag(QGraphicsItem::ItemIsMovable);

}

void HighwayWindow::drawRoad(unsigned nLanes) {
    if (nLanes != 0) nLanes_ = nLanes;
    lanes_.clear();
    for (unsigned i = 0; i < nLanes_; i++) {
        lanes_.push_back(std::make_shared<Lane>(this, i));
        ui->roadLayout->addLayout(lanes_.back().get());
    }
}

HighwayWindow::~HighwayWindow()
{
    delete ui;
}
