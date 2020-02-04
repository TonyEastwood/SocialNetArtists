#include "headers/openglviewer.h"
#include "ui_openglviewer.h"

double scale_x = 3;                         // that need to zoom in or zoom out
double scale_y = 3;                         // that need to zoom in or zoom out
double scale_z = 3;                         // that need to zoom in or zoom out
double rotate_y = 0;                        // that need for rotate Object
double rotate_x = 0;                        // that need for rotate Object
double rotate_z = 0;                        // that need for rotate Object
std::vector<std::vector<double>> vector_3d; // vector that consist all vectors that we will draw
OpenGlViewer::OpenGlViewer(QWidget *parent)
    : QOpenGLWidget(parent)
{
    ui->setupUi(this);
}

OpenGlViewer::~OpenGlViewer()
{
    delete ui;
}

void OpenGlViewer::initializeGL()
{

    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    // initShaders();
    // initTextures();

    //! [2]
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);
}

void OpenGlViewer::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}

void OpenGlViewer::paintGL()
{

    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture->bind();

    //! [6]
    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -5.0);
    matrix.rotate(rotation);

    // Set modelview-projection matrix
    program.setUniformValue("mvp_matrix", projection * matrix);
    //! [6]

    // Use texture unit 0 which contains cube.png
    program.setUniformValue("texture", 0);

    // Draw cube geometry
    // geom->drawCubeGeometry(&program);
}

void OpenGlViewer::mousePressEvent(QMouseEvent *event)
{
    mousePressPosition = QVector2D(event->localPos());
}

void OpenGlViewer::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        rotate_y = event->x() - x_pos; // rotate Object on x
        rotate_x = event->y() - y_pos; // rotate Object on y
        this->update();                // update Form that display Object
    }
}

void OpenGlViewer::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}

void OpenGlViewer::timerEvent(QTimerEvent *e)
{
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01)
    {
        angularSpeed = 0.0;
    }
    else
    {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

        // Request an update
        update();
    }
}
