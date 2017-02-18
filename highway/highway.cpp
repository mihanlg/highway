#include "highway.h"
#include "ui_highway.h"
#include <iostream>


Highway::Highway(QWidget *parent, unsigned nLanes) :
    QMainWindow(parent),
    ui(new Ui::HighwayWindow),
    nLanes_(nLanes)
{
    ui->setupUi(this);
    settings_ = std::make_shared<Settings>();
    settings_->setMinSpeed(ui->spinMinSpeedBox->value());
    settings_->setMaxSpeed(ui->spinMaxSpeedBox->value());
}

Highway::~Highway()
{
    delete ui;
}

void Highway::drawHighway(unsigned nLanes) {
    if (nLanes == 0) nLanes = nLanes_;
    lanes_.clear();
    nLanes_ = 0;
    for (unsigned i = 0; i < nLanes; i++) {
        addLane();
    }
}

void Highway::addLane() {
    lanes_.push_back(std::make_shared<Lane>(settings_, this->parentWidget(), nLanes_++));
    ui->roadLayout->addLayout(lanes_.back().get());
}

void Highway::removeLane() {
    lanes_.pop_back();
    nLanes_--;
}

void Highway::on_addLaneButton_clicked()
{
    if (nLanes_ < maxLanes_) {
        addLane();
    }
}

void Highway::on_deleteLaneButton_clicked()
{
    if (nLanes_ > 1) {
        removeLane();
    }
}

void Highway::on_spinMinSpeedBox_valueChanged(int val)
{
    if (val > ui->spinMaxSpeedBox->value()) {
        ui->spinMaxSpeedBox->setValue(val);
    }
    settings_->setMinSpeed(val);
}

void Highway::on_spinMaxSpeedBox_valueChanged(int val)
{
    if (val < ui->spinMinSpeedBox->value()) {
        ui->spinMinSpeedBox->setValue(val);
    }
    settings_->setMaxSpeed(val);
}

void Highway::on_addCarButton_clicked()
{
    int i = rand()%lanes_.size();
    lanes_[i]->addCar();
}
