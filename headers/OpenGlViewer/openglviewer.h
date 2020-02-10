#ifndef OPENGLVIEWER_H
#define OPENGLVIEWER_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include "headers/objectManagement/object3d.h"
//#include <QtOpenGL>
//#include <QOpenGLShaderProgram>
//#include <QOpenGLTexture>
#include <QElapsedTimer>
namespace Ui {
class OpenGlViewer;
}

class OpenGlViewer : public QGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  explicit OpenGlViewer(Object3d _object, QWidget *parent = nullptr);
  ~OpenGlViewer() override;

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;  // object roration
  void mouseReleaseEvent(QMouseEvent *e) override;
  void wheelEvent(QWheelEvent *event) override;  // object scale

  // void timerEvent(QTimerEvent *e) override;
 private:
  void drawGrid();

  void drawLines();
  void drawTriangles();
  void drawSquads();

 private:
  QElapsedTimer *timerForTest;

  int openGlwidth, openGlheight;           // window size
  Object3d drawObject;                     // object that need to draw
  float x_pos, y_pos, rotate_y, rotate_x;  // rotate values
  int scaleWheel = 2;                      // current scale (zoom in\zoom out)
  Ui::OpenGlViewer *ui;

  std::vector<primitives::Point3d> vertexData;

  std::vector<primitives::Line3d> linesData;  // load lines data from object

  std::vector<primitives::Triangle3d>
      trianglesData;                          // get triangles data from object
  std::vector<primitives::Face3d> facesData;  // load faces from object
  uint vertexVSize, linesVSize, trianglesVSize,
      facesVSize;  // quantity vertex/lines/triangles/faces

  int maxOrigin;  // max value of coords x/y/z
};

#endif  // OPENGLVIEWER_H
