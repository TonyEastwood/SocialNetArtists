#include <QApplication>

#include "headers/mainappwindow.h"
#include "headers/mainwindow.h"
#include "headers/objectManagement/objectparsemanager.h"
#include "headers/objectManagement/objectstoragemanager.h"
int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  qDebug() << "Start";
  ObjectParseManager parser;
  // Object3d testObject = parser.fromStlToObject("test.stl");
  // testObject.setObjectName("myObj");

  Object3d testObject2 = parser.fromObjToObject("test.obj");

  ObjectStorageManager blabla("someDir");
  blabla.addNewObject(testObject2);
  qDebug() << "Vertex= " << testObject2.getQuantityVertex3d()
           << "Line= " << testObject2.getQuantityLines3d()
           << "Triangle= " << testObject2.getQuantityTriangles3d()
           << "Faces= " << testObject2.getQuantityFaces3d();
  Object3d qw;
  MainWindow w;
  MainAppWindow ew(testObject2);
  ew.show();
  w.show();
  qDebug() << "End";
  return a.exec();
  // Vertex=  519577 Line=  1872738 Triangle=  624102 Faces=  108
}
