#ifndef LANE_H
#define LANE_H

#include <QObject>
#include <QtWidgets>

class Lane : public QVBoxLayout
{
    Q_OBJECT
public:
    explicit Lane(QWidget *parent = 0, unsigned idLane = 0);
    ~Lane();

signals:

public slots:
private:
    unsigned idLane_;
    QGraphicsView *laneView;
    QHBoxLayout *buttonsLayout;
    QPushButton *button;
    QGraphicsScene *scene;
    //QGraphicsRectItem *rectangle;
};

#endif // LANE_H
