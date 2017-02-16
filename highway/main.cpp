#include "highwaywindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HighwayWindow w;
    w.show();
    w.drawRoad(10);
    //QTimer timer;
    //QObject::connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
    //timer.start(1000 / 33);

    return a.exec();
}
