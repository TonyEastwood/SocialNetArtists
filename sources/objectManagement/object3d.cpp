#include "../../headers/objectManagement/object3d.h"

object3d::object3d() { headerInfo = "default"; }

object3d::~object3d() {}
/*!
     \brief get header info.

      detail...
 */
QByteArray object3d::getHeaderInfo() const { return headerInfo; }
/*!
     \brief set header info.

      detail...
 */
void object3d::setHeaderInfo(const QByteArray &value) { headerInfo = value; }
/*!
     \brief get quantity triangle3d.

      detail...
 */
unsigned int object3d::getQuantityTriangles3d() const {
  return triangles3dData.size();
}

unsigned int object3d::getCurrentVertexIndex() const {
  return vertex3dData.size() - 1;
}

unsigned int object3d::getCurrentLineIndex() const {
  return lines3dData.size() - 1;
}

unsigned int object3d::getCurrentTriangleIndex() const {
  return triangles3dData.size() - 1;
}

unsigned int object3d::getCurrentFaceIndex() const {
  return faces3dData.size() - 1;
}
/*!
     \brief set quantity triangle3d.

      detail...
 */

/*!
     \brief add triangle to triangle3d array current object.

      detail...
 */
void object3d::addtriangle3d(const primitives::triangle3d _triangle) {
  setMaxOriginAxis(vertex3dData[_triangle.indexVertex1]);
  setMaxOriginAxis(vertex3dData[_triangle.indexVertex2]);
  setMaxOriginAxis(vertex3dData[_triangle.indexVertex3]);
  triangles3dData.push_back(_triangle);
}

void object3d::addVertex3d(const primitives::point3d _vertex) {
  vertex3dData.push_back(_vertex);
}

void object3d::addLine3d(const primitives::line3d _line) {
  lines3dData.push_back(_line);
}

void object3d::addFace3d(const primitives::face3d _face) {
  faces3dData.push_back(_face);
}

std::vector<primitives::triangle3d> object3d::getTrianglesData() {
  return triangles3dData;
}

primitives::point3d object3d::getMaxOriginAxis() const { return maxOriginAxis; }

std::vector<primitives::point3d> object3d::getVertex3dData() const {
  return vertex3dData;
}

std::vector<primitives::line3d> object3d::getLines3dData() const {
  return lines3dData;
}

std::vector<primitives::face3d> object3d::getFaces3dData() const {
  return faces3dData;
}

void object3d::setMaxOriginAxis(const primitives::point3d _point) {
  if (maxOriginAxis.x < abs(_point.x)) maxOriginAxis.x = abs(_point.x);
  if (maxOriginAxis.y < abs(_point.y)) maxOriginAxis.y = abs(_point.y);
  if (maxOriginAxis.z < abs(_point.z)) maxOriginAxis.z = abs(_point.z);
}
