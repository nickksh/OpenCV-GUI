#include "qcwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCWidget w;
    w.show();

    return a.exec();
}
