#ifndef MAINAPPWINDOW_H
#define MAINAPPWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QVBoxLayout>

#include "OpenGlViewer/openglviewer.h"
namespace Ui {
class MainAppWindow;
}

class MainAppWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainAppWindow(Object3d _object, QWidget *parent = nullptr);
  ~MainAppWindow();

 private:
  Ui::MainAppWindow *ui;
  OpenGlViewer *openGlViewer;  // openGl viewer
  QHBoxLayout *mainLayout;
};

#endif  // MAINAPPWINDOW_H
