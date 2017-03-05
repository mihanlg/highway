#include "laneview.h"
#include <iostream>

LaneView::LaneView() {
    rotate(180.0);
}

void LaneView::resizeEvent(QResizeEvent *event)
{
    auto g = frameRect();
    setSceneRect(baseLaneX, baseCarLength, baseLaneWidth, g.height());
    QWidget::resizeEvent(event);
}
