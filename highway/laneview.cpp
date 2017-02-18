#include "laneview.h"
#include <iostream>

void LaneView::resizeEvent(QResizeEvent *event)
{
    auto g = frameRect();
    setSceneRect(baseLaneX, -g.height(), baseLaneWidth, g.height());
    QWidget::resizeEvent(event);
}
