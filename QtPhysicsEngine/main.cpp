#include "QtPhysicsEngine.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtPhysicsEngine w;
    w.show();
    return a.exec();
}
