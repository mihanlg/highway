#ifndef LANEVIEW_H
#define LANEVIEW_H

#include <QtWidgets>
#include "settings.h"


class LaneView : public QGraphicsView
{
public:
    LaneView();
private:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // LANEVIEW_H
