#include "headers/mainwindow.h"
#include "headers/objectparsemanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "Start";
    ObjectParseManager parser;
    parser.parseStlObject("test2.stl");
    // MainWindow w;
    // w.show();
    qDebug() << "End";
    return a.exec();
}
