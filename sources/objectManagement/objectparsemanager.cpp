#include "../../headers/objectManagement/objectparsemanager.h"

ObjectParseManager::ObjectParseManager()
{
}

ObjectParseManager::~ObjectParseManager()
{
}
/*!
     \brief method that convert stl file to object.

      detail...
 */
object3d ObjectParseManager::fromStlToObject(const QByteArray fileName)
{
    object3d object;
    QFile stlFile(fileName);
    if (stlFile.open(QIODevice::ReadOnly))
    {
        object.setHeaderInfo(stlFile.read(80));                                   // set header info
        uint quantityTriangles = *((uint*)stlFile.read(4).toStdString().c_str()); // get quantity triangles

        for (uint i = 0; i < quantityTriangles; i++)
        {
            auto normal = to3dPoint(stlFile.read(12)); // get triangles normal
            auto v1 = to3dPoint(stlFile.read(12));
            auto v2 = to3dPoint(stlFile.read(12));
            auto v3 = to3dPoint(stlFile.read(12));

            object.addTriangles(primitives::triangles(
                normal, v1, v2, v3)); // add triangles to triangles array that object contain
            stlFile.read(2);          // miss two bytes
        }
    }
    return object;
}
/*!
     \brief method that convert bytes to float.

      detail...
 */
float ObjectParseManager::toFloat(const QByteArray bytes)
{
    return *((float*)bytes.toStdString().c_str());
}
/*!
     \brief method that convert bytes to 3d point.

      detail...
 */
primitives::point3d ObjectParseManager::to3dPoint(QByteArray bytes)
{
    return primitives::point3d(toFloat(bytes.mid(0, 4)), toFloat(bytes.mid(4, 8)), toFloat(bytes.mid(8, 12)));
}
