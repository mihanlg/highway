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
    ui->spinMaxSpeedBox->setValue(100);
    ui->spinMinSpeedBox->setValue(40);
    ui->spinMinAccBox->setValue(0.1);
    ui->spinMaxAccBox->setValue(1.0);
    ui->spinMaxDecBox->setValue(1.5);
    ui->autoAppearCheckButton->setChecked(false);
    ui->spinMinAppearTimeBox->setValue(0.1);
    ui->spinMaxAppearTimeBox->setValue(1.0);

    settings_->setMinSpeed(ui->spinMinSpeedBox->value());
    settings_->setMaxSpeed(ui->spinMaxSpeedBox->value());
    settings_->setMinAcceleration(ui->spinMinAccBox->value());
    settings_->setMaxAcceleration(ui->spinMaxAccBox->value());
    settings_->setMaxDeceleration(ui->spinMaxDecBox->value());
    settings_->setAutoAppear(ui->autoAppearCheckButton->isChecked());
    settings_->setMinAppearTime(ui->spinMinAppearTimeBox->value());
    settings_->setMaxAppearTime(ui->spinMaxAppearTimeBox->value());

    timer = std::make_shared<QTimer>();
    connect(timer.get(), SIGNAL(timeout()), this, SLOT(addRandomCarWithTimer()));
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

void Highway::addRandomCarWithTimer() {
    timer->stop();
    addRandomCar();
    double t = settings_->getRandomAppearTime();
    timer->setInterval(t);
    timer->start();
}

void Highway::addRandomCar() {
    int i = rand()%lanes_.size();
    lanes_[i]->addCar();
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
    addRandomCar();
}

void Highway::on_spinMinAccBox_valueChanged(double val)
{
    settings_->setMinAcceleration(val);
}

void Highway::on_spinMaxAccBox_valueChanged(double val)
{
    settings_->setMaxAcceleration(val);
}

void Highway::on_spinMaxDecBox_valueChanged(double val)
{
    settings_->setMaxDeceleration(val);
}

void Highway::on_autoAppearCheckButton_clicked()
{
    settings_->setAutoAppear(ui->autoAppearCheckButton->isChecked());
    if (ui->autoAppearCheckButton->isChecked()) {
        double t = settings_->getRandomAppearTime();
        timer->setInterval(t);
        timer->start();
    }
    else timer->stop();
}

void Highway::on_spinMinAppearTimeBox_valueChanged(double val)
{
    if (val > ui->spinMaxAppearTimeBox->value()) {
        ui->spinMaxAppearTimeBox->setValue(val);
    }
    settings_->setMinAppearTime(val);
}

void Highway::on_spinMaxAppearTimeBox_valueChanged(double val)
{
    if (val < ui->spinMinAppearTimeBox->value()) {
        ui->spinMinAppearTimeBox->setValue(val);
    }
    settings_->setMaxAppearTime(val);
}
