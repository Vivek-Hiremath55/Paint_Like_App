#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtWidgetsApplication1 w;
    // w.resize(860, 876);
    w.show();
    return a.exec();
}
