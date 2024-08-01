#include "mainwindow.h"
#include "binaryreader.h"
#include "constellationwidget.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(QApplication::translate("application", "Constellation"));

    w.show();
    return a.exec();
}
