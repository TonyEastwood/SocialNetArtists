#ifndef OPENGLVIEWER_H
#define OPENGLVIEWER_H

//#include <QWidget>
#include <QOpenGLWidget>
namespace Ui {
class OpenGlViewer;
}

class OpenGlViewer : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit OpenGlViewer(QWidget *parent = nullptr);
    ~OpenGlViewer();

private:
    Ui::OpenGlViewer *ui;
};

#endif // OPENGLVIEWER_H
