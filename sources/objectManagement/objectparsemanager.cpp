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
        QList<QByteArray> values; // values that will contains parse data
        QByteArray currentLine;
        float x, y, z;
        uint p[12] = { 0 };
        while (!objFile.atEnd())
        {
            currentLine = objFile.readLine();

            if (currentLine[0] == 'v') // if current line containts vertex coords
            {
                if (currentLine[1] == 't'
                    || currentLine[1]
                        == 'n') // ignore texture and normal direction [need to modify in future version]
                    continue;

                values = currentLine.mid(2).trimmed().split(' '); // parse coords from line
                x = values[0].toFloat();
                y = values[1].toFloat();
                z = values[2].toFloat();

                object.addVertex3d({ x, y, z }); // add vertex to array
            }
            else if (currentLine[0] == 'l') // if current line contains data about line3d
            {
                values = currentLine.mid(2).trimmed().split(' ');             // parse vertex data from line
                object.addLine3d({ values[0].toUInt(), values[1].toUInt() }); // add line to lines3D array
            }
            else if (currentLine[0] == 'f') // if current line contains data about faces or triangles
            {
                QList<QByteArray> valuesAfterFaceParse; // data after parsing separate vertex of face

                values = currentLine.mid(2).trimmed().split(' '); // parse faces data from line

                if (values.size() == 4) // if current data relate to face
                {
                    for (uint i = 0, j = 0; i < 4; ++i, j += 3)
                    {
                        valuesAfterFaceParse = values[i].split('/'); // parse each vertex in face
                        p[j] = valuesAfterFaceParse[0].toUInt();     // get vertex index
                    }
                    for (uint i = 0; i < 12;
                         ++i) // correct indexes. Index in obj format start from 1, in c++ from 0, so..
                        p[i] -= 1;

                    object.addLine3d({ p[0], p[3] }); // add 4 lines ( face = 4 lines) to lines array
                    object.addLine3d({ p[3], p[6] });
                    object.addLine3d({ p[6], p[9] });
                    object.addLine3d({ p[0], p[9] });

                    object.addFace3d({ 0, p[0], p[3], p[6], p[9] }); // add face to array of faces
                }
                else if (values.size() == 3) // if current data relate to triangles
                {
                    for (uint i = 0, j = 0; i < 3; ++i, j += 3)
                    {
                        valuesAfterFaceParse = values[i].split('/'); // parse each vertex in triangles
                        p[j] = valuesAfterFaceParse[0].toUInt();     // get vertex index
                    }
                    for (uint i = 0; i < 12;
                         ++i) // correct indexes. Index in obj format start from 1, in c++ from 0, so..
                        p[i] -= 1;

                    object.addLine3d({ p[0], p[3] }); // add 3 lines ( triangles = 3 lines) to lines array
                    object.addLine3d({ p[3], p[6] });
                    object.addLine3d({ p[6], p[0] });

                    object.addTriangle3d({ 0, p[0], p[3], p[6] }); // add triangles to array of triangles
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
