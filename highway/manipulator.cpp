#include "manipulator.h"
#include "ui_manipulator.h"
#include <iostream>


Manipulator::Manipulator(unsigned nLanes, QWidget *parent) :
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
    ui->autoAppearCheckBox->setChecked(false);
    ui->spinMinAppearTimeBox->setValue(2.5);
    ui->spinMaxAppearTimeBox->setValue(3.5);
    ui->spinMinDistanceBox->setValue(0.3);
    ui->spinMaxDistanceBox->setValue(2.0);
    ui->autoFixCheckBox->setChecked(false);
    ui->spinAutoFixTimeBox->setEnabled(false);
    ui->spinAutoFixTimeBox->setValue(15);
    ui->pauseButton->setChecked(false);
    ui->nextFrameButton->setEnabled(false);
    ui->spinCrawlingSpeedBox->setValue(10);
    ui->carTextComboBox->setCurrentIndex(0);
    ui->reactionSlider->setValue(10);
    ui->spinMinCarLengthBox->setValue(40);
    ui->spinMaxCarLengthBox->setValue(80);

    settings_->setMinSpeed(ui->spinMinSpeedBox->value());
    settings_->setMaxSpeed(ui->spinMaxSpeedBox->value());
    settings_->setMinAcceleration(ui->spinMinAccBox->value());
    settings_->setMaxAcceleration(ui->spinMaxAccBox->value());
    settings_->setMaxDeceleration(ui->spinMaxDecBox->value());
    settings_->setAutoAppear(ui->autoAppearCheckBox->isChecked());
    settings_->setMinAppearTime(ui->spinMinAppearTimeBox->value());
    settings_->setMaxAppearTime(ui->spinMaxAppearTimeBox->value());
    settings_->setMinDistance(ui->spinMinDistanceBox->value());
    settings_->setMaxDistance(ui->spinMaxDistanceBox->value());
    settings_->setAutoFixTime(ui->spinAutoFixTimeBox->value());
    settings_->setAutoFixState(ui->autoFixCheckBox->isChecked());
    settings_->setCrawlingSpeed(ui->spinCrawlingSpeedBox->value());
    settings_->setShowSpeed(showNothing);
    settings_->setPause(ui->pauseButton->isChecked());
    settings_->setReaction(ui->reactionSlider->value());
    settings_->setMinCarLength(ui->spinMinCarLengthBox->value());
    settings_->setMaxCarLength(ui->spinMaxCarLengthBox->value());

    highway_ = std::make_shared<Highway>(settings_);
    drawHighway(nLanes);
    updateNLanesLabel();
}

Manipulator::~Manipulator()
{
    delete ui;
}


//INTERFACE
void Manipulator::updateNLanesLabel() {
    std::string nLabelsString = std::to_string(highway_->getNLanes());

    ui->nLanesLabel->setText(nLabelsString.c_str());
}

void Manipulator::on_addLaneButton_clicked()
{
    Lane* lane = highway_->addLane();
    if (lane) {
        ui->roadLayout->addLayout(lane);
        updateNLanesLabel();
    }
}

void Manipulator::drawHighway(unsigned nLanes) {
    if (nLanes == 0) nLanes = highway_->getSize();
    highway_->clear();
    for (unsigned i = 0; i < nLanes; ++i) {
        Lane* lane = highway_->addLane();
        ui->roadLayout->addLayout(lane);
    }
}

void Manipulator::on_deleteLaneButton_clicked()
{
    highway_->deleteLane();
    updateNLanesLabel();
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
    highway_->addRandomCar();
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

void Manipulator::on_autoFixCheckBox_stateChanged(int val)
{
    ui->spinAutoFixTimeBox->setEnabled(val);
    settings_->setAutoFixState(val);
}

void Manipulator::on_cleanButton_clicked()
{
    highway_->clean();
}

void Manipulator::on_pauseButton_clicked()
{
    settings_->setPause(ui->pauseButton->isChecked());
    ui->nextFrameButton->setEnabled(settings_->isPaused());
    highway_->checkTimers();
}

void Manipulator::on_nextFrameButton_clicked()
{
    highway_->startUpdateTimer();
    if (ui->autoAppearCheckBox->isChecked()) {
        highway_->startAddRandomCarTimer();
    }
}

void Manipulator::on_spinCrawlingSpeedBox_valueChanged(int val)
{
    settings_->setCrawlingSpeed(val);
}

void Manipulator::on_zoomOutButton_clicked()
{
    highway_->scale(-5.);
}

void Manipulator::on_zoomInButton_clicked()
{
    highway_->scale(5.);
}

void Manipulator::on_autoAppearCheckBox_clicked()
{
    settings_->setAutoAppear(ui->autoAppearCheckBox->isChecked());
    if (ui->autoAppearCheckBox->isChecked()) {
        double t = settings_->getRandomAppearTime();
        highway_->setAddRandomCarTimerInterval(t);
        highway_->startAddRandomCarTimer();
    }
    else highway_->stopAddRandomCarTimer();
}

void Manipulator::on_carTextComboBox_activated(int index)
{
    switch (index) {
    case 0: settings_->setShowSpeed(showNothing);
        break;
    case 1: settings_->setShowSpeed(showSpeed);
        break;
    case 2: settings_->setShowSpeed(showNumber);
        break;
    case 3: settings_->setShowSpeed(showStatus);
        break;
    case 4: settings_->setShowSpeed(showPosition);
        break;
    default: break;
    }
}

void Manipulator::on_reactionSlider_sliderMoved(int val)
{
    settings_->setReaction(static_cast<unsigned>(val));
}

void Manipulator::on_spinMinCarLengthBox_valueChanged(int val)
{
    if (val > ui->spinMaxCarLengthBox->value()) {
        ui->spinMaxCarLengthBox->setValue(val);
    }
    settings_->setMinCarLength(val);
}

void Manipulator::on_spinMaxCarLengthBox_valueChanged(int val)
{
    if (val < ui->spinMinCarLengthBox->value()) {
        ui->spinMinCarLengthBox->setValue(val);
    }
    settings_->setMaxCarLength(val);
}
