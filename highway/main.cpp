#include "highway.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Highway w;
    w.show();
    w.drawHighway();
    //QTimer timer;
    //QObject::connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
    //timer.start(1000 / 33);

    return a.exec();
}
