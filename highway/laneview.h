#ifndef LANEVIEW_H
#define LANEVIEW_H

#include <QtWidgets>
#include "settings.h"


class LaneView : public QGraphicsView
{
public:
    LaneView(std::shared_ptr<Settings> &settings);
    void setScale(double ds);
private:
    void resizeEvent(QResizeEvent *event) override;
private:
    std::shared_ptr<Settings> settings_;
};

#endif // LANEVIEW_H
