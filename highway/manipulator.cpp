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
    ui->spinMinAppearTimeBox->setValue(0.1);
    ui->spinMaxAppearTimeBox->setValue(1.0);
    ui->spinMinDistanceBox->setValue(1.5);
    ui->spinMaxDistanceBox->setValue(3.0);
    ui->autoFixCheckBox->setChecked(false);
    ui->spinAutoFixTimeBox->setEnabled(false);
    ui->spinAutoFixTimeBox->setValue(15);
    ui->pauseButton->setChecked(false);
    ui->nextFrameButton->setEnabled(false);
    ui->spinCrawlingSpeedBox->setValue(10);
    ui->carTextComboBox->setCurrentIndex(0);
    ui->reactionSlider->setValue(20);

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

    updateTimer_ = std::make_shared<QTimer>();
    updateTimer_->setInterval(updateTime_);
    connect(updateTimer_.get(), SIGNAL(timeout()), this, SLOT(updateLanes()));
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
        if (lanes_.size() && lanes_.back()->isClosed()) {
            lanes_.back()->open();
        }
        else if (lanes_.size() < maxLanes_) {
            std::weak_ptr<Lane> left;
            if (lanes_.size() > 0) left = lanes_.back();
            std::shared_ptr<Lane> newLane = std::make_shared<Lane>(settings_, left, this->parentWidget(), lanes_.size());
            if (lanes_.size() > 0)
                lanes_.back()->setRight(newLane);
            lanes_.push_back(newLane);
            ui->roadLayout->addLayout(lanes_.back().get());
        }
    }
    updateNLanesLabel();
}

void Manipulator::deleteLane() {
    if (lanes_.size() > 1) {
        if (lanes_.back()->isClosed()) {
            if (lanes_.back()->isEmptyLane()) {
                lanes_.pop_back();
            }
        } else lanes_.back()->close();
    }
    updateNLanesLabel();
}


void Manipulator::addRandomCarWithTimer() {
    addRandomCarTimer_->stop();
    addRandomCar();
    double t = settings_->getRandomAppearTime();
    addRandomCarTimer_->setInterval(t);
    addRandomCarTimer_->start();
}

void Manipulator::addRandomCar() {
    int max_l = lanes_.size();
    if (lanes_.back()->isClosed()) max_l--;
    int i = rand()%max_l;
    lanes_[i]->addCar();
}

void Manipulator::checkTimers() {
    if (settings_->isPaused()) {
        if (updateTimer_->isActive()) updateTimer_->stop();
        if (addRandomCarTimer_->isActive() && ui->autoAppearCheckBox->isChecked()) {
            addRandomCarTimer_->setInterval(addRandomCarTimer_->remainingTime());
            addRandomCarTimer_->stop();
        }
    } else {
        if (!updateTimer_->isActive()) {
            updateTimer_->start();
        }
        if (ui->autoAppearCheckBox->isChecked()) {
            if (!addRandomCarTimer_->isActive()) {
                addRandomCarTimer_->start();
            }
        }
    }
}

void Manipulator::updateLanes() {
    checkTimers();
    ui->deleteLaneButton->setEnabled(lanes_.back()->isOpened());
    if (!lanes_.back()->isOpened()) {
        deleteLane();
    }
    for (auto lane: lanes_) {
        lane->updateCars();
    }
}

void Manipulator::clean() {
    for (auto lane: lanes_) {
        lane->clean();
    }
}

//INTERFACE
void Manipulator::updateNLanesLabel() {
    std::string nLabelsString = std::to_string(lanes_.size());
    ui->nLanesLabel->setText(nLabelsString.c_str());
}

void Manipulator::on_addLaneButton_clicked()
{
    addLane();
    updateNLanesLabel();
}

void Manipulator::on_deleteLaneButton_clicked()
{
    deleteLane();
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
    clean();
}

void Manipulator::on_pauseButton_clicked()
{
    settings_->setPause(ui->pauseButton->isChecked());
    ui->nextFrameButton->setEnabled(settings_->isPaused());
    checkTimers();
}

void Manipulator::on_nextFrameButton_clicked()
{
    updateTimer_->start();
    if (ui->autoAppearCheckBox->isChecked()) {
        addRandomCarTimer_->start();
    }
}

void Manipulator::on_spinCrawlingSpeedBox_valueChanged(int val)
{
    settings_->setCrawlingSpeed(val);
}

void Manipulator::scale(qreal s) {
    for (auto lane: lanes_) {
        lane->scale(s);
    }
}

void Manipulator::on_zoomOutButton_clicked()
{

}

void Manipulator::on_zoomInButton_clicked()
{
    scale(2.0);
}

void Manipulator::on_autoAppearCheckBox_clicked()
{
    settings_->setAutoAppear(ui->autoAppearCheckBox->isChecked());
    if (ui->autoAppearCheckBox->isChecked()) {
        double t = settings_->getRandomAppearTime();
        addRandomCarTimer_->setInterval(t);
        addRandomCarTimer_->start();
    }
    else addRandomCarTimer_->stop();
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
    default: break;
    }
}

void Manipulator::on_reactionSlider_sliderMoved(int val)
{
    settings_->setReaction(static_cast<unsigned>(val));
}
