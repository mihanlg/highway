#ifndef HIGHWAY_H
#define HIGHWAY_H

#include <QMainWindow>
#include <QGraphicsItem>
#include <QtWidgets>
#include <vector>
#include <memory>

#include "lane.h"
#include "settings.h"

#define maxLanes_ 10

namespace Ui {
class HighwayWindow;
}

class Highway : public QMainWindow
{
    Q_OBJECT

public:
    explicit Highway(QWidget *parent = 0, unsigned nLanes = 1);
    ~Highway();
    void drawHighway(unsigned nLanes = 0);
    void addLane();
    void removeLane();
private slots:
    void addRandomCarWithTimer();
    void addRandomCar();

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

private:
    Ui::HighwayWindow *ui;
    unsigned nLanes_;
    std::shared_ptr<Settings> settings_;
    std::vector<std::shared_ptr<Lane>> lanes_;
    std::shared_ptr<QTimer> timer;
};

#endif // HIGHWAY_H
