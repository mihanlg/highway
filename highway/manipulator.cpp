#include "manipulator.h"
#include "ui_manipulator.h"
#include <iostream>


Manipulator::Manipulator(QWidget *parent, unsigned nLanes) :
    QMainWindow(parent),
    ui(new Ui::ManipulatorWindow)
{
    ui->setupUi(this);
    settings_ = std::make_shared<Settings>();
    ui->spinMaxSpeedBox->setValue(120);
    ui->spinMinSpeedBox->setValue(90);
    ui->spinMinAccBox->setValue(0.1);
    ui->spinMaxAccBox->setValue(1.0);
    ui->spinMaxDecBox->setValue(2.0);
    ui->autoAppearCheckButton->setChecked(false);
    ui->spinMinAppearTimeBox->setValue(0.1);
    ui->spinMaxAppearTimeBox->setValue(1.0);
    ui->spinMinDistanceBox->setValue(1.5);
    ui->spinMaxDistanceBox->setValue(3.0);

    settings_->setMinSpeed(ui->spinMinSpeedBox->value());
    settings_->setMaxSpeed(ui->spinMaxSpeedBox->value());
    settings_->setMinAcceleration(ui->spinMinAccBox->value());
    settings_->setMaxAcceleration(ui->spinMaxAccBox->value());
    settings_->setMaxDeceleration(ui->spinMaxDecBox->value());
    settings_->setAutoAppear(ui->autoAppearCheckButton->isChecked());
    settings_->setMinAppearTime(ui->spinMinAppearTimeBox->value());
    settings_->setMaxAppearTime(ui->spinMaxAppearTimeBox->value());
    settings_->setMinDistance(ui->spinMinDistanceBox->value());
    settings_->setMaxDistance(ui->spinMaxDistanceBox->value());

    updateTimer_ = std::make_shared<QTimer>();
    updateTimer_->setInterval(40);
    connect(updateTimer_.get(), SIGNAL(timeout()), this, SLOT(updateCars()));
    updateTimer_->start();

    addRandomCarTimer_ = std::make_shared<QTimer>();
    connect(addRandomCarTimer_.get(), SIGNAL(timeout()), this, SLOT(addRandomCarWithTimer()));

    drawHighway(nLanes);
}

Manipulator::~Manipulator()
{
    delete ui;
}

void Manipulator::drawHighway(unsigned nLanes) {
    if (nLanes == 0) nLanes = lanes_.size();
    lanes_.clear();
    addLane(nLanes);
}

void Manipulator::addLane(unsigned nLanes) {
    for (unsigned i = 0; i < nLanes; i++) {
        if (lanes_.size() < maxLanes_) {
            lanes_.push_back(std::make_shared<Lane>(settings_, this->parentWidget(), lanes_.size()));
            ui->roadLayout->addLayout(lanes_.back().get());
        }
    }
}

void Manipulator::deleteLane() {
    if (lanes_.size() > 1) {
        lanes_.pop_back();
    }
}


void Manipulator::addRandomCarWithTimer() {
    addRandomCarTimer_->stop();
    addRandomCar();
    double t = settings_->getRandomAppearTime();
    addRandomCarTimer_->setInterval(t);
    addRandomCarTimer_->start();
}

void Manipulator::addRandomCar() {
    int i = rand()%lanes_.size();
    lanes_[i]->addCar();
}

void Manipulator::updateCars() {
    for (auto lane: lanes_) {
        lane->updateCars();
    }
}

//INTERFACE
void Manipulator::on_addLaneButton_clicked()
{
    addLane();
}

void Manipulator::on_deleteLaneButton_clicked()
{
    deleteLane();
}

void Manipulator::on_spinMinSpeedBox_valueChanged(int val)
{
    if (val > ui->spinMaxSpeedBox->value()) {
        ui->spinMaxSpeedBox->setValue(val);
    }
    settings_->setMinSpeed(val);
}

void Manipulator::on_spinMaxSpeedBox_valueChanged(int val)
{
    if (val < ui->spinMinSpeedBox->value()) {
        ui->spinMinSpeedBox->setValue(val);
    }
    settings_->setMaxSpeed(val);
}

void Manipulator::on_addCarButton_clicked()
{
    addRandomCar();
}

void Manipulator::on_spinMinAccBox_valueChanged(double val)
{
    settings_->setMinAcceleration(val);
}

void Manipulator::on_spinMaxAccBox_valueChanged(double val)
{
    settings_->setMaxAcceleration(val);
}

void Manipulator::on_spinMaxDecBox_valueChanged(double val)
{
    settings_->setMaxDeceleration(val);
}

void Manipulator::on_autoAppearCheckButton_clicked()
{
    settings_->setAutoAppear(ui->autoAppearCheckButton->isChecked());
    if (ui->autoAppearCheckButton->isChecked()) {
        double t = settings_->getRandomAppearTime();
        addRandomCarTimer_->setInterval(t);
        addRandomCarTimer_->start();
    }
    else addRandomCarTimer_->stop();
}

void Manipulator::on_spinMinAppearTimeBox_valueChanged(double val)
{
    if (val > ui->spinMaxAppearTimeBox->value()) {
        ui->spinMaxAppearTimeBox->setValue(val);
    }
    settings_->setMinAppearTime(val);
}

void Manipulator::on_spinMaxAppearTimeBox_valueChanged(double val)
{
    if (val < ui->spinMinAppearTimeBox->value()) {
        ui->spinMinAppearTimeBox->setValue(val);
    }
    settings_->setMaxAppearTime(val);
}

void Manipulator::on_spinMinDistanceBox_valueChanged(double val)
{
    if (val > ui->spinMaxDistanceBox->value()) {
        ui->spinMaxDistanceBox->setValue(val);
    }
    settings_->setMinDistance(val);
}

void Manipulator::on_spinMaxDistanceBox_valueChanged(double val)
{
    if (val < ui->spinMinDistanceBox->value()) {
        ui->spinMinDistanceBox->setValue(val);
    }
    settings_->setMaxDistance(val);
}
