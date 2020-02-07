#ifndef OBJECT3D_H
#define OBJECT3D_H
#include <QByteArray>
#include <QtMath>
#include <vector>

#include "objectinterface.h"
class Object3d : public ObjectInterface
{
public:
    Object3d();
    ~Object3d();

    QByteArray getName() const;
    void setObjectName(const QByteArray &value);

    unsigned int getQuantityVertex3d() const;    // return vertex array size
    unsigned int getQuantityLines3d() const;     // return lines array size
    unsigned int getQuantityTriangles3d() const; // return triangles array size
    unsigned int getQuantityFaces3d() const;     // return faces array size

    unsigned int getCurrentVertexIndex() const;   // get index on last element of vertex array
    unsigned int getCurrentLineIndex() const;     // get index on last element of lines array
    unsigned int getCurrentTriangleIndex() const; // get index on last element of triangles array
    unsigned int getCurrentFaceIndex() const;     // get index on last element of faces array

    void addVertex3d(const primitives::Point3d _vertex);        // add coords to vertex array
    void addLine3d(const primitives::Line3d _line);             // add line to lines array
    void addTriangle3d(const primitives::Triangle3d _triangle); // add triangle to triangles array
    void addFace3d(const primitives::Face3d _face);             // add face to faces array

    std::vector<primitives::Point3d> getVertex3dData() const; // get vertex array
    std::vector<primitives::Line3d> getLines3dData() const;   // get lines array
    std::vector<primitives::Triangle3d> getTrianglesData();   // get triangles array
    std::vector<primitives::Face3d> getFaces3dData() const;   // get faces array

    primitives::Point3d getMaxOriginAxis() const;

private:
    QByteArray objectName; // must contain only letters and numbs:
    // obJect1 || SomeObject23234,

    std::vector<primitives::Point3d> vertex3dData;       // data that contain vertex coords
    std::vector<primitives::Line3d> lines3dData;         // data that contain lines
    std::vector<primitives::Triangle3d> triangles3dData; // data that contain triangles
    std::vector<primitives::Face3d> faces3dData;         // data that contain faces

    primitives::Point3d maxOriginAxis{
        0, 0, 0
    }; // max value on axis X,Y,Z (need to set start scale in openglViewer)

private:
    void setMaxOriginAxis(const primitives::Point3d _point);
};

#endif // OBJECT3D_H
