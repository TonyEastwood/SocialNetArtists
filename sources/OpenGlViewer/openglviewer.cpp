#include "../../headers/OpenGlViewer/openglviewer.h"

#include "ui_openglviewer.h"
#include <QDebug>

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
    glEnable(GL_DEPTH_TEST);  // line that we can't see - become invisible

    //    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);    //to enable transparency. In future version
    //    uncomment glEnable(GL_BLEND);                         //to enable transparency. In future version
    //    uncomment glClearColor(0.0, 0.0, 0.0, 0.0);           //to enable transparency. In future version
    //    uncomment
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
    int scale = 3;
    glOrtho(-scale * drawObject.getMaxOriginAxis().x, scale * drawObject.getMaxOriginAxis().x,
            scale * drawObject.getMaxOriginAxis().y, -scale * drawObject.getMaxOriginAxis().y,
            -scale * drawObject.getMaxOriginAxis().z,
            scale * drawObject.getMaxOriginAxis().z); // set matrix scope (2*x,2*y,2*z)

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // camera rotation
    glRotatef(rotate_x, 1.0, 0.0, 0.0); // rotate x
    glRotatef(rotate_y, 0.0, 1.0, 0.0); // rotate y

    // cube();

    std::vector<primitives::point3d> vertexData =
        drawObject.getVertex3dData(); // load vertex data from object

    if (!drawObject.getFaces3dData().empty()) // if array of faces not empty -> draw faces
    {
        std::vector<primitives::face3d> facesData = drawObject.getFaces3dData(); // load faces from object
        uint quantityFaces3d = drawObject.getQuantityFaces3d();                  // get quantity lines

        glBegin(GL_QUADS);           // START FACES DRAWING
        glColor3f(0.0f, 1.0f, 1.0f); // set faces color
        for (uint i = 0; i < quantityFaces3d; ++i)
        {

            glVertex3f(vertexData[facesData[i].indexVertex1].x, vertexData[facesData[i].indexVertex1].y,
                       vertexData[facesData[i].indexVertex1].z);
            glVertex3f(vertexData[facesData[i].indexVertex2].x, vertexData[facesData[i].indexVertex2].y,
                       vertexData[facesData[i].indexVertex2].z);
            glVertex3f(vertexData[facesData[i].indexVertex3].x, vertexData[facesData[i].indexVertex3].y,
                       vertexData[facesData[i].indexVertex3].z);
            glVertex3f(vertexData[facesData[i].indexVertex4].x, vertexData[facesData[i].indexVertex4].y,
                       vertexData[facesData[i].indexVertex4].z);
        }
        glEnd(); // END TRIANGLES DRAWING
    }
    if (!drawObject.getTrianglesData().empty()) // if triangle array not empty -> draw triangles
    {
        std::vector<primitives::triangle3d> trianglesData =
            drawObject.getTrianglesData();                              // get triangles data from object
        uint quantityTrianlges3d = drawObject.getQuantityTriangles3d(); // get quantity of triangles

        glBegin(GL_TRIANGLES);       // START TRIANGLES DRAWING
        glColor3f(1.0f, 1.0f, 0.0f); // set triangles color
        for (uint i = 0; i < quantityTrianlges3d; ++i)
        {
            glVertex3f(vertexData[trianglesData[i].indexVertex1].x,
                       vertexData[trianglesData[i].indexVertex1].y,
                       vertexData[trianglesData[i].indexVertex1].z);
            glVertex3f(vertexData[trianglesData[i].indexVertex2].x,
                       vertexData[trianglesData[i].indexVertex2].y,
                       vertexData[trianglesData[i].indexVertex2].z);
            glVertex3f(vertexData[trianglesData[i].indexVertex3].x,
                       vertexData[trianglesData[i].indexVertex3].y,
                       vertexData[trianglesData[i].indexVertex3].z);
        }
        glEnd(); // END TRIANGLES DRAWING
    }

    if (!drawObject.getLines3dData().empty()) // if lines array not empty -> draw lines
    {
        std::vector<primitives::line3d> linesData =
            drawObject.getLines3dData();                        // load lines data from object
        uint quantityLines3d = drawObject.getQuantityLines3d(); // get quantity lines
        glLineWidth(20);                                        // set line width
        glBegin(GL_LINES);                                      // START LINES DRAWING
        glColor3f(1.0f, 0.0f, 0.0f);                            // set line color
        for (uint i = 0; i < quantityLines3d; ++i)
        {
            glVertex3f(vertexData[linesData[i].indexVertex1].x, vertexData[linesData[i].indexVertex1].y,
                       vertexData[linesData[i].indexVertex1].z);
            glVertex3f(vertexData[linesData[i].indexVertex2].x, vertexData[linesData[i].indexVertex2].y,
                       vertexData[linesData[i].indexVertex2].z);
        }
        glEnd(); // END LINES DRAWING
    }

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
