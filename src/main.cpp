#include "Screens/mainwindow.h"
#include "Screens/sequencediagramwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();
    return a.exec();
}
