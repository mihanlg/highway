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
#define updateTime_ 40

namespace Ui {
class ManipulatorWindow;
}

class Manipulator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Manipulator(unsigned nLanes = 1, QWidget *parent = 0);
    ~Manipulator();
    void drawHighway(unsigned nLanes = 0);
private slots:
    void updateNLanesLabel();
    void addLane(unsigned nLanes = 1);
    void deleteLane();
    void addRandomCarWithTimer();
    void addRandomCar();
    void updateLanes();
    void clean();
    void checkTimers();
    void scale(qreal s);

    //INTERFACE
    void on_addLaneButton_clicked();
    void on_deleteLaneButton_clicked();
    void on_addCarButton_clicked();
    void on_spinMinSpeedBox_valueChanged(int val);
    void on_spinMaxSpeedBox_valueChanged(int val);
    void on_spinMinAccBox_valueChanged(double val);
    void on_spinMaxAccBox_valueChanged(double val);
    void on_spinMaxDecBox_valueChanged(double val);
    void on_spinMinAppearTimeBox_valueChanged(double val);
    void on_spinMaxAppearTimeBox_valueChanged(double val);
    void on_spinMinDistanceBox_valueChanged(double val);
    void on_spinMaxDistanceBox_valueChanged(double val);
    void on_autoFixCheckBox_stateChanged(int val);
    void on_cleanButton_clicked();
    void on_pauseButton_clicked();
    void on_nextFrameButton_clicked();
    void on_spinCrawlingSpeedBox_valueChanged(int val);
    void on_zoomOutButton_clicked();
    void on_zoomInButton_clicked();
    void on_autoAppearCheckBox_clicked();
    void on_carTextComboBox_activated(int index);

    void on_reactionSlider_sliderMoved(int val);

private:
    Ui::ManipulatorWindow *ui;
    std::shared_ptr<Settings> settings_;
    std::shared_ptr<QTimer> updateTimer_, addRandomCarTimer_;
    std::vector<std::shared_ptr<Lane>> lanes_;
    std::weak_ptr<Car> carToShowInfo;
};

#endif // MANIPULATOR_H
