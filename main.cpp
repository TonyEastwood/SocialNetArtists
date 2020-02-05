#include "headers/mainwindow.h"
#include "headers/objectparsemanager.h"
#include <QApplication>
#include "headers/mainappwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "Start";
    ObjectParseManager parser;
    object3d testObject = parser.fromStlToObject("test3.stl");
    MainWindow w;
    MainAppWindow ew(testObject);
    ew.show();
    w.show();
    qDebug() << "End";
    return a.exec();
}
