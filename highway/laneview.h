#ifndef LANEVIEW_H
#define LANEVIEW_H

#include <QtWidgets>

#define baseLaneWidth 50
#define baseLaneX -baseLaneWidth/2
#define minLaneHeight 300

class LaneView : public QGraphicsView
{
public:
private:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // LANEVIEW_H
