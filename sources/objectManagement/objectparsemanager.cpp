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
        stlFile.read(80);                                                          // set header info
        uint quantitytriangle3d = *((uint*)stlFile.read(4).toStdString().c_str()); // get quantity triangle3d

        uint currentVertexIndex = 0;
        for (uint i = 0; i < quantitytriangle3d; ++i)
        {
            for (int j = 0; j < 4; ++j)
                object.addVertex3d(to3dPoint(stlFile.read(12))); // add vertex to data

            currentVertexIndex = object.getCurrentVertexIndex(); // get current vertex index

            object.addLine3d(
                { currentVertexIndex - 2, currentVertexIndex - 1 });          // add line (point2 and point3)
            object.addLine3d({ currentVertexIndex - 2, currentVertexIndex }); // add line (point1 and point3)
            object.addLine3d({ currentVertexIndex - 1, currentVertexIndex }); // add line (point1 and point2)

            object.addTriangle3d(primitives::triangle3d(currentVertexIndex - 3, currentVertexIndex - 2,
                                                        currentVertexIndex - 1,
                                                        currentVertexIndex)); // add triangle3d to triangle3d
                                                                              // array that object contain
            stlFile.read(2);                                                  // miss two bytes
        }
        stlFile.close();
    }
    else
        qDebug() << "Cannot open the file " << fileName;
    return object;
}

object3d ObjectParseManager::fromObjToObject(const QByteArray fileName)
{
    object3d object;

    QFile objFile(fileName);
    if (objFile.open(QIODevice::ReadOnly))
    {
        object.setHeaderInfo("ObjFile"); // set header info
        QByteArray currentLine;
        float x, y, z;
        uint p[12] = { 0 };
        while (!objFile.atEnd())
        {
            currentLine = objFile.readLine();

            if (currentLine[0] == 'v')
            {
                if (currentLine[1] == 't' || currentLine[1] == 'n')
                    continue;

                QList<QByteArray> values = currentLine.mid(2).trimmed().split(' ');
                x = values[0].toFloat();
                y = values[1].toFloat();
                z = values[2].toFloat();

                object.addVertex3d({ x, y, z });
            }
            else if (currentLine[0] == 'l')
            {
                QList<QByteArray> values = currentLine.mid(2).trimmed().split(' ');
                p[0] = values[0].toUInt();
                p[1] = values[1].toUInt();

                // sscanf(currentLine.mid(2), "%d %d\n", &p[0], &p[1]);
                object.addLine3d({ p[0], p[1] });
            }
            else if (currentLine[0] == 'f')
            {
                QList<QByteArray> values = currentLine.mid(2).trimmed().split(' ');
                if (values.size() == 4)
                {
                    QList<QByteArray> values2;
                    for (uint i = 0, j = 0; i < 4; ++i, j += 3)
                    {
                        values2 = values[i].split('/');
                        p[j] = values2[0].toUInt();
                    }

                    //                if (sscanf(currentLine.mid(2), "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n",
                    //                &p[0], &p[1], &p[2],
                    //                           &p[3], &p[4], &p[5], &p[6], &p[7], &p[8], &p[9], &p[10],
                    //                           &p[11])
                    //                    == 12)
                    //                {
                    for (uint i = 0; i < 12; ++i)
                        p[i] -= 1;
                    object.addLine3d({ p[0], p[3] });
                    object.addLine3d({ p[3], p[6] });
                    object.addLine3d({ p[6], p[9] });
                    object.addLine3d({ p[0], p[9] });

                    object.addFace3d({ 0, p[0], p[3], p[6], p[9] }); // replace 0 with normal!!!!!!
                }
                else if (values.size() == 3)
                {
                    QList<QByteArray> values2;
                    for (uint i = 0, j = 0; i < 3; ++i, j += 3)
                    {
                        values2 = values[i].split('/');
                        p[j] = values2[0].toUInt();
                    }
                    for (uint i = 0; i < 12; ++i)
                        p[i] -= 1;
                    object.addLine3d({ p[0], p[3] });
                    object.addLine3d({ p[3], p[6] });
                    object.addLine3d({ p[6], p[0] });

                    object.addTriangle3d({ 0, p[0], p[3], p[6] }); // replace 0 with normal!!!!
                }
            }
        }
        objFile.close();
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
