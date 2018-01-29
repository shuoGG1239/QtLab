#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(358,378);
    w.setWindowTitle("Designed For WifiPiano");
    w.show();

    return a.exec();
}
