#include "../headers/object3d.h"

object3d::object3d()
{
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
    return quantityTriangles;
}
/*!
     \brief set quantity triangles.

      detail...
 */
void object3d::setQuantityTriangles(unsigned int value)
{
    quantityTriangles = value;
}
/*!
     \brief add triangle to triangles array current object.

      detail...
 */
void object3d::addTriangles(const object3d::triangles _triangle)
{
    trianglesData.push_back(_triangle);
}
