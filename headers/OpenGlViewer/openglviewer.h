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

namespace Ui {
class OpenGlViewer;
}

class OpenGlViewer : public QGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit OpenGlViewer(object3d _object, QWidget *parent = nullptr);
    ~OpenGlViewer() override;

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void wheelEvent(QWheelEvent *event) override;

    // void timerEvent(QTimerEvent *e) override;

private:
    int openGlwidth, openGlheight;          // window size
    object3d drawObject;                    // object that need to draw
    float x_pos, y_pos, rotate_y, rotate_x; // rotate values
    int scaleWheel = 1;
    Ui::OpenGlViewer *ui;
};

#endif // OPENGLVIEWER_H
