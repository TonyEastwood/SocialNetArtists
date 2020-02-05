#include "../headers/object3d.h"

object3d::object3d()
{
    headerInfo = "default";
}

object3d::~object3d()
{
}
/*!
     \brief get header info.

      detail...
 */
QByteArray object3d::getHeaderInfo() const
{
    return headerInfo;
}
/*!
     \brief set header info.

      detail...
 */
void object3d::setHeaderInfo(const QByteArray &value)
{
    headerInfo = value;
}
/*!
     \brief get quantity triangles.

      detail...
 */
unsigned int object3d::getQuantityTriangles() const
{
    return trianglesData.size();
}
/*!
     \brief set quantity triangles.

      detail...
 */

/*!
     \brief add triangle to triangles array current object.

      detail...
 */
void object3d::addTriangles(const primitives::triangles _triangle)
{
    setMaxOriginAxis(_triangle.point1);
    setMaxOriginAxis(_triangle.point2);
    setMaxOriginAxis(_triangle.point3);
    trianglesData.push_back(_triangle);
}

std::vector<primitives::triangles> object3d::getTrianglesData()
{
    return trianglesData;
}

primitives::point3d object3d::getMaxOriginAxis() const
{
    return maxOriginAxis;
}

void object3d::setMaxOriginAxis(const primitives::point3d _point)
{
    if (maxOriginAxis.x < abs(_point.x))
        maxOriginAxis.x = abs(_point.x);
    if (maxOriginAxis.y < abs(_point.y))
        maxOriginAxis.y = abs(_point.y);
    if (maxOriginAxis.z < abs(_point.z))
        maxOriginAxis.z = abs(_point.z);
}
