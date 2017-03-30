#include "laneview.h"
#include <iostream>

LaneView::LaneView(std::shared_ptr<Settings> &settings) : settings_(settings) {
    rotate(180.0);
}

void LaneView::resizeEvent(QResizeEvent *event)
{
    auto g = frameRect();
    setSceneRect(baseLaneX, baseCarLength, baseLaneWidth, g.height()/settings_->getScale());
    QWidget::resizeEvent(event);
}

void LaneView::setScale(double ds) {
    scale(ds, ds);
    resizeEvent(0);
}
