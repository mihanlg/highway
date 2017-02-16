#ifndef HIGHWAYWINDOW_H
#define HIGHWAYWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>
#include <QtWidgets>
#include <vector>
#include <memory>
#include "lane.h"


namespace Ui {
class HighwayWindow;
}

class HighwayWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HighwayWindow(QWidget *parent = 0, unsigned nLanes = 1);
    ~HighwayWindow();
    void drawRoad(unsigned nLanes = 0);
private:
    Ui::HighwayWindow *ui;
    unsigned nLanes_;
    std::vector<std::shared_ptr<Lane>> lanes_;
};

#endif // HIGHWAYWINDOW_H
