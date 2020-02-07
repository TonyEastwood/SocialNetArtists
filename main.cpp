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

    ObjectStorageManager blabla("someDir");
    blabla.addNewObject(testObject);

    MainWindow w;
    MainAppWindow ew(blabla.getObjectFromListByName(blabla.getObjectsList()[0]));
    ew.show();
    w.show();
    qDebug() << "End";
    return a.exec();
}
