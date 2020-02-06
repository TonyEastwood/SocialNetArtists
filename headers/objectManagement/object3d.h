#ifndef OBJECT3D_H
#define OBJECT3D_H
#include <QByteArray>
#include <QtMath>
#include <vector>

#include "objectinterface.h"
class object3d : public ObjectInterface {
 public:
  object3d();
  ~object3d();

  QByteArray getHeaderInfo() const;
  void setHeaderInfo(const QByteArray &value);

  unsigned int getQuantityVertex3d() const;
  unsigned int getQuantityLines3d() const;
  unsigned int getQuantityTriangles3d() const;
  unsigned int getQuantityFaces3d() const;

  unsigned int getCurrentVertexIndex() const;
  unsigned int getCurrentLineIndex() const;
  unsigned int getCurrentTriangleIndex() const;
  unsigned int getCurrentFaceIndex() const;

  void addVertex3d(const primitives::point3d _vertex);
  void addLine3d(const primitives::line3d _line);
  void addtriangle3d(const primitives::triangle3d _triangle);
  void addFace3d(const primitives::face3d _face);

  std::vector<primitives::point3d> getVertex3dData() const;
  std::vector<primitives::line3d> getLines3dData() const;
  std::vector<primitives::triangle3d> getTrianglesData();
  std::vector<primitives::face3d> getFaces3dData() const;

  primitives::point3d getMaxOriginAxis() const;

 private:
  QByteArray headerInfo;

  std::vector<primitives::point3d> vertex3dData;
  std::vector<primitives::line3d> lines3dData;
  std::vector<primitives::triangle3d> triangles3dData;
  std::vector<primitives::face3d> faces3dData;

  primitives::point3d maxOriginAxis{
      0, 0,
      0};  // max value on axis X,Y,Z (need to set start scale in openglViewer
  void setMaxOriginAxis(const primitives::point3d _point);
};

#endif  // OBJECT3D_H
