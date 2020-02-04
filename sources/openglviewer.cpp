#include "headers/openglviewer.h"
#include "ui_openglviewer.h"

OpenGlViewer::OpenGlViewer(QWidget *parent)
    : QOpenGLWidget(parent)
{
    ui->setupUi(this);
}

OpenGlViewer::~OpenGlViewer()
{
    delete ui;
}
