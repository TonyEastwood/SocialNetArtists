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
        object.setHeaderInfo(stlFile.read(80));                                    // set header info
        uint quantitytriangle3d = *((uint*)stlFile.read(4).toStdString().c_str()); // get quantity triangle3d

        for (uint i = 0; i < quantitytriangle3d; i++)
        {
            auto normal = to3dPoint(stlFile.read(12)); // get triangle3d normal
            auto v1 = to3dPoint(stlFile.read(12));
            auto v2 = to3dPoint(stlFile.read(12));
            auto v3 = to3dPoint(stlFile.read(12));

            object.addtriangle3d(primitives::triangle3d(
                normal, v1, v2, v3)); // add triangle3d to triangle3d array that object contain
            stlFile.read(2);          // miss two bytes
        }
    }
    else
        qDebug() << "Cannot open the file " << fileName;
    return object;
}

object3d ObjectParseManager::fromObjToObject(const QByteArray fileName)
{
    object3d object;
    QFile stlFile(fileName);
    if (stlFile.open(QIODevice::ReadOnly))
    {
        std::vector<primitives::point3d> vertex;

        object.setHeaderInfo(stlFile.read(80));                                    // set header info
        uint quantitytriangle3d = *((uint*)stlFile.read(4).toStdString().c_str()); // get quantity triangle3d

        for (uint i = 0; i < quantitytriangle3d; i++)
        {
            auto normal = to3dPoint(stlFile.read(12)); // get triangle3d normal
            auto v1 = to3dPoint(stlFile.read(12));
            auto v2 = to3dPoint(stlFile.read(12));
            auto v3 = to3dPoint(stlFile.read(12));

            object.addtriangle3d(primitives::triangle3d(
                normal, v1, v2, v3)); // add triangle3d to triangle3d array that object contain
            stlFile.read(2);          // miss two bytes
        }
    }
    else
        qDebug() << "Cannot open the file " << fileName;
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
