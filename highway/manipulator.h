#ifndef MANIPULATOR_H
#define MANIPULATOR_H

#include <QMainWindow>
#include <QGraphicsItem>
#include <QtWidgets>

#include <vector>
#include <memory>

#include "lane.h"
#include "settings.h"

#define maxLanes_ 10

namespace Ui {
class ManipulatorWindow;
}

class Manipulator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Manipulator(QWidget *parent = 0, unsigned nLanes = 1);
    ~Manipulator();
    void drawHighway(unsigned nLanes = 0);
private slots:
    void addLane(unsigned nLanes = 1);
    void deleteLane();

    void addRandomCarWithTimer();
    void addRandomCar();

    void updateCars();

    //INTERFACE
    void on_addLaneButton_clicked();
    void on_deleteLaneButton_clicked();
    void on_addCarButton_clicked();

    void on_spinMinSpeedBox_valueChanged(int val);
    void on_spinMaxSpeedBox_valueChanged(int val);
    void on_spinMinAccBox_valueChanged(double val);
    void on_spinMaxAccBox_valueChanged(double val);
    void on_spinMaxDecBox_valueChanged(double val);

    void on_autoAppearCheckButton_clicked();
    void on_spinMinAppearTimeBox_valueChanged(double val);
    void on_spinMaxAppearTimeBox_valueChanged(double val);

    void on_spinMinDistanceBox_valueChanged(double val);
    void on_spinMaxDistanceBox_valueChanged(double val);

private:
    Ui::ManipulatorWindow *ui;
    std::shared_ptr<Settings> settings_;
    std::shared_ptr<QTimer> updateTimer_, addRandomCarTimer_;
    std::vector<std::shared_ptr<Lane>> lanes_;
};

#endif // MANIPULATOR_H
