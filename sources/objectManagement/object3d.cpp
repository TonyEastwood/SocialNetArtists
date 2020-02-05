#include "../../headers/objectManagement/object3d.h"

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
     \brief get quantity triangle3d.

      detail...
 */
unsigned int object3d::getQuantitytriangle3d() const
{
    return triangle3dData.size();
}
/*!
     \brief set quantity triangle3d.

      detail...
 */

/*!
     \brief add triangle to triangle3d array current object.

      detail...
 */
void object3d::addtriangle3d(const primitives::triangle3d _triangle)
{
    setMaxOriginAxis(_triangle.point1);
    setMaxOriginAxis(_triangle.point2);
    setMaxOriginAxis(_triangle.point3);
    triangle3dData.push_back(_triangle);
}

std::vector<primitives::triangle3d> object3d::gettriangle3dData()
{
    return triangle3dData;
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
