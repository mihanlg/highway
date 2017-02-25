#include "manipulator.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Manipulator man;
    man.show();
    man.drawHighway();
    return a.exec();
}
