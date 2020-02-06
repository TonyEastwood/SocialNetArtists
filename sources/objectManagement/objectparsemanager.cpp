#include "../../headers/objectManagement/objectparsemanager.h"

ObjectParseManager::ObjectParseManager() {}

ObjectParseManager::~ObjectParseManager() {}
/*!
     \brief method that convert stl file to object.

      detail...
 */
object3d ObjectParseManager::fromStlToObject(const QByteArray fileName) {
  object3d object;
  QFile stlFile(fileName);
  if (stlFile.open(QIODevice::ReadOnly)) {
    object.setHeaderInfo(stlFile.read(80));  // set header info
    uint quantitytriangle3d = *((uint*)stlFile.read(4)
                                    .toStdString()
                                    .c_str());  // get quantity triangle3d

    uint currentVertexIndex = 0;
    for (uint i = 0; i < quantitytriangle3d; ++i) {
      //      auto normal = to3dPoint(stlFile.read(12));  // get triangle3d
      //      normal auto v1 = to3dPoint(stlFile.read(12)); auto v2 =
      //      to3dPoint(stlFile.read(12)); auto v3 =
      //      to3dPoint(stlFile.read(12));

      for (int j = 0; j < 4; ++j)
        object.addVertex3d(to3dPoint(stlFile.read(12)));
      currentVertexIndex = object.getCurrentVertexIndex();

      object.addtriangle3d(primitives::triangle3d(
          currentVertexIndex - 3, currentVertexIndex - 2,
          currentVertexIndex - 1,
          currentVertexIndex));  // add triangle3d to triangle3d array that
                                 // object contain
      stlFile.read(2);           // miss two bytes
    }
    stlFile.close();
  } else
    qDebug() << "Cannot open the file " << fileName;
  return object;
}

object3d ObjectParseManager::fromObjToObject(const QByteArray fileName) {
  object3d object;
  QFile stlFile(fileName);
  if (stlFile.open(QIODevice::ReadOnly)) {
    object.setHeaderInfo("ObjFile");  // set header info
    QByteArray currentLine;
    float x, y, z;
    uint p1, p2, p3, p4;
    while (!stlFile.atEnd()) {
      currentLine = stlFile.readLine();

      if (currentLine[0] == 'v') {
        sscanf(currentLine.mid(2), "%f %f %f\n", &x, &y, &z);
        object.addVertex3d({x, y, z});

      } else if (currentLine[0] == 'l') {
        sscanf(currentLine.mid(2), "%d %d\n", &p1, &p2);
        object.addLine3d({p1, p2});

      } else if (currentLine[0] == 'f') {
        if (sscanf(currentLine.mid(2), "%d/ %d/ %d/ %d/\n", &p1, &p2, &p3,
                   &p4) == 4) {
          object.addFace3d({0, p1, p2, p3, p4});  // replace 0 with normal!!!!!!
        } else if (sscanf(currentLine.mid(2), "%d/ %d/ %d/\n", &p1, &p2, &p3) ==
                   3) {
          object.addtriangle3d({0, p1, p2, p3});  // replace 0 with normal!!!!
        } else
          qDebug() << "[Error] Error when parsing face from obj";
      }
    }
  } else
    qDebug() << "Cannot open the file " << fileName;
  return object;
}
/*!
     \brief method that convert bytes to float.

      detail...
 */
float ObjectParseManager::toFloat(const QByteArray bytes) {
  return *((float*)bytes.toStdString().c_str());
}
/*!
     \brief method that convert bytes to 3d point.

      detail...
 */
primitives::point3d ObjectParseManager::to3dPoint(QByteArray bytes) {
  return primitives::point3d(toFloat(bytes.mid(0, 4)), toFloat(bytes.mid(4, 8)),
                             toFloat(bytes.mid(8, 12)));
}
