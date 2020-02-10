#include "../../headers/objectManagement/object3d.h"

Object3d::Object3d()
{
    objectName = "default";
}

Object3d::~Object3d()
{
}
/*!
     \brief get header info.

      detail...
 */
QByteArray Object3d::getName() const
{
    return objectName;
}
/*!
     \brief set header info.

      detail...
 */
void Object3d::setObjectName(const QByteArray &value)
{
    objectName = value;
}

unsigned int Object3d::getQuantityVertex3d() const
{
    return vertex3dData.size();
}

unsigned int Object3d::getQuantityLines3d() const
{
    return lines3dData.size();
}
/*!
     \brief get quantity Triangle3d.

      detail...
 */
unsigned int Object3d::getQuantityTriangles3d() const
{
    return triangles3dData.size();
}

unsigned int Object3d::getQuantityFaces3d() const
{
    return faces3dData.size();
}

unsigned int Object3d::getCurrentVertexIndex() const
{
    return vertex3dData.size() - 1;
}

unsigned int Object3d::getCurrentLineIndex() const
{
    return lines3dData.size() - 1;
}

unsigned int Object3d::getCurrentTriangleIndex() const
{
    return triangles3dData.size() - 1;
}

unsigned int Object3d::getCurrentFaceIndex() const
{
    return faces3dData.size() - 1;
}
/*!
     \brief set quantity Triangle3d.

      detail...
 */

/*!
     \brief add triangle to Triangle3d array current object.

      detail...
 */
void Object3d::addTriangle3d(const primitives::Triangle3d _triangle)
{
    triangles3dData.push_back(_triangle);
}

void Object3d::addVertex3d(const primitives::Point3d _vertex)
{
    setMaxOriginAxis(_vertex);
    vertex3dData.push_back(_vertex);
}

void Object3d::addLine3d(const primitives::Line3d _line)
{
    lines3dData.push_back(_line);
}

void Object3d::addFace3d(const primitives::Face3d _face)
{
    faces3dData.push_back(_face);
}

std::vector<primitives::Triangle3d> Object3d::getTrianglesData()
{
    return triangles3dData;
}

int Object3d::getMaxOriginAxis() const
{
    return maxOrigin;
}

std::vector<primitives::Point3d> Object3d::getVertex3dData() const
{
    return vertex3dData;
}

std::vector<primitives::Line3d> Object3d::getLines3dData() const
{
    return lines3dData;
}

std::vector<primitives::Face3d> Object3d::getFaces3dData() const
{
    return faces3dData;
}

void Object3d::setMaxOriginAxis(const primitives::Point3d _point)
{
    if (maxOrigin < abs(_point.x))
        maxOrigin = abs(_point.x);
    if (maxOrigin < abs(_point.y))
        maxOrigin = abs(_point.y);
    if (maxOrigin < abs(_point.z))
        maxOrigin = abs(_point.z);
}
