#include "highway.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Highway w;
    w.show();
    w.drawHighway();
    return a.exec();
}
