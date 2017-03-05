#include "manipulator.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Manipulator man(3);
    man.show();
    return a.exec();
}
