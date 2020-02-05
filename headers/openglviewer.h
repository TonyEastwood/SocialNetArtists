#ifndef OPENGLVIEWER_H
#define OPENGLVIEWER_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
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
    explicit OpenGlViewer(QWidget *parent = nullptr);
    ~OpenGlViewer() override;

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    // void timerEvent(QTimerEvent *e) override;

private:
    int openGlwidth, openGlheight; // window size

    float x_pos, y_pos, rotate_y, rotate_x; // rotate values
    Ui::OpenGlViewer *ui;
};

#endif // OPENGLVIEWER_H
