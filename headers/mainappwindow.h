#ifndef MAINAPPWINDOW_H
#define MAINAPPWINDOW_H

#include <QMainWindow>
#include "openglviewer.h"
#include <QVBoxLayout>

namespace Ui {
class MainAppWindow;
}

class MainAppWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainAppWindow(object3d _object, QWidget *parent = nullptr);
    ~MainAppWindow();

private:
    Ui::MainAppWindow *ui;
    OpenGlViewer *openGlViewer; // openGl viewer
    QHBoxLayout *mainLayout;
};

#endif // MAINAPPWINDOW_H
