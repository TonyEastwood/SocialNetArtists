#include <QApplication>

#include "headers/mainappwindow.h"
#include "headers/mainwindow.h"
#include "headers/objectManagement/objectparsemanager.h"
#include "headers/objectManagement/objectstoragemanager.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "Start";
    ObjectParseManager parser;
    Object3d testObject = parser.fromStlToObject("test2.stl");

    // Object3d testObject2 = parser.fromObjToObject("cube.obj");
    MainWindow w;
    MainAppWindow ew(testObject);
    ObjectStorageManager blabla("someDir");
    blabla.addNewObject(testObject);
    ew.show();
    w.show();
    qDebug() << "End";
    return a.exec();
}
