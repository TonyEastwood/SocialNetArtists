#include "../../headers/OpenGlViewer/openglviewer.h"

#include "ui_openglviewer.h"

OpenGlViewer::OpenGlViewer(object3d _object, QWidget *parent)
    : QGLWidget(parent)
{
    ui->setupUi(this);
    drawObject = _object;
    openGlwidth = 500;                       // window width
    openGlheight = 500;                      // window height
    setFormat(QGLFormat(QGL::DoubleBuffer)); // double buff
}

OpenGlViewer::~OpenGlViewer()
{
    delete ui;
}

void OpenGlViewer::initializeGL()
{
    initializeOpenGLFunctions();
    glDepthFunc(GL_LEQUAL);   // buff deep
    qglClearColor(Qt::black); // set background black
}

void OpenGlViewer::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLint)w, (GLint)h);
    openGlwidth = w;
    openGlheight = h;
}
void cube()
{
    float value = 100;

    glBegin(GL_QUADS);
    glVertex2f(-value / 4, value / 4);  // vertex 1
    glVertex2f(-value / 2, -value / 4); // vertex 2
    glVertex2f(value / 2, -value / 4);  // vertex 3
    glVertex2f(value / 4, value / 4);   // vertex 4
    glEnd();

    glBegin(GL_QUADS); // Begin drawing the color cube with 6 quads

    glColor3f(value, value, 0.0f); // Green
    glVertex3f(value, value, -value);
    glVertex3f(-value, value, -value);
    glVertex3f(-value, value, value);
    glVertex3f(value, value, value);

    // Bottom face (y = -value)
    glColor3f(value, value / 2, 0.0f); // Orange
    glVertex3f(value, -value, value);
    glVertex3f(-value, -value, value);
    glVertex3f(-value, -value, -value);
    glVertex3f(value, -value, -value);

    // Front face  (z = value)
    glColor3f(value, 0.0f, 0.0f); // Red
    glVertex3f(value, value, value);
    glVertex3f(-value, value, value);
    glVertex3f(-value, -value, value);
    glVertex3f(value, -value, value);

    // Back face (z = -value)
    glColor3f(value, value, 0.0f); // Yellow
    glVertex3f(value, -value, -value);
    glVertex3f(-value, -value, -value);
    glVertex3f(-value, value, -value);
    glVertex3f(value, value, -value);

    // Left face (x = -value)
    glColor3f(0.0f, 0.0f, value); // Blue
    glVertex3f(-value, value, value);
    glVertex3f(-value, value, -value);
    glVertex3f(-value, -value, -value);
    glVertex3f(-value, -value, value);

    // Right face (x = value)
    glColor3f(value, 0.0f, value); // Magenta
    glVertex3f(value, value, -value);
    glVertex3f(value, value, value);
    glVertex3f(value, -value, value);
    glVertex3f(value, -value, -value);
    glEnd(); // End of drawing color-cube
}
void OpenGlViewer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear buff image and deep
    glMatrixMode(GL_PROJECTION);                        // set the matrix
    glShadeModel(GL_SMOOTH);
    glLoadIdentity(); // load matrix
                      //    glOrtho(-openGlwidth, openGlwidth, openGlheight, -openGlheight, -500,
                      //            500); // set matrix scope (x,y,z)
    glOrtho(-2 * drawObject.getMaxOriginAxis().x, 2 * drawObject.getMaxOriginAxis().x,
            2 * drawObject.getMaxOriginAxis().y, -2 * drawObject.getMaxOriginAxis().x,
            -2 * drawObject.getMaxOriginAxis().z,
            2 * drawObject.getMaxOriginAxis().z); // set matrix scope (x,y,z)

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glRotatef(rotate_x, 1.0, 0.0, 0.0); // rotate x
    glRotatef(rotate_y, 0.0, 1.0, 0.0); // rotate y

    // cube();
    uint quantityTriangles = drawObject.getQuantityTriangles();
    std::vector<primitives::triangles> data = drawObject.getTrianglesData();
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 0.0f);
    for (int i = 0; i < quantityTriangles; ++i)
    {

        glVertex3f(data[i].point1.x, data[i].point1.y, data[i].point1.z);
        glVertex3f(data[i].point2.x, data[i].point2.y, data[i].point2.z);
        glVertex3f(data[i].point3.x, data[i].point3.y, data[i].point3.z);
    }
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 0.0f);
    for (int i = 0; i < quantityTriangles; ++i)
    {

        glVertex3f(data[i].point1.x, data[i].point1.y, data[i].point1.z);
        glVertex3f(data[i].point2.x, data[i].point2.y, data[i].point2.z);

        glVertex3f(data[i].point2.x, data[i].point2.y, data[i].point2.z);
        glVertex3f(data[i].point3.x, data[i].point3.y, data[i].point3.z);

        glVertex3f(data[i].point1.x, data[i].point1.y, data[i].point1.z);
        glVertex3f(data[i].point3.x, data[i].point3.y, data[i].point3.z);
    }
    glEnd();

    doubleBuffer();
}

void OpenGlViewer::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    { // memorize coords x and y mouse when we start clicking
        x_pos = event->x();
        y_pos = event->y();
    }
}

void OpenGlViewer::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        rotate_y = event->x() - x_pos; // rotate Object on x
        rotate_x = event->y() - y_pos; // rotate Object on y
        update();                      // update Form that display Object
    }
}

void OpenGlViewer::mouseReleaseEvent(QMouseEvent *e)
{
    x_pos = 0;
    y_pos = 0;
    // Mouse release position - mouse press position
}

// void OpenGlViewer::timerEvent(QTimerEvent *e) {}
