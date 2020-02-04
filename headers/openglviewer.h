#ifndef OPENGLVIEWER_H
#define OPENGLVIEWER_H

//#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
namespace Ui {
class OpenGlViewer;
}

class OpenGlViewer : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit OpenGlViewer(QWidget *parent = nullptr);
    ~OpenGlViewer();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void timerEvent(QTimerEvent *e) override;

private:
    Ui::OpenGlViewer *ui;
    QBasicTimer timer;
    QOpenGLShaderProgram program;

    QOpenGLTexture *texture;

    QMatrix4x4 projection;

    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    QOpenGLFunctions *geom;
    qreal angularSpeed;
    QQuaternion rotation;
    // QtLogo *logo;
    double x_pos; // position mouse on x
    double y_pos;
    int xRot;
    int yRot;
    int zRot;
    QPoint lastPos;
    QColor qtGreen;
    QColor qtPurple;
};

#endif // OPENGLVIEWER_H
