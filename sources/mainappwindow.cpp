#include "headers/mainappwindow.h"

#include <QLabel>

#include "ui_mainappwindow.h"

MainAppWindow::MainAppWindow(Object3d _object, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainAppWindow) {
  //[unused]
  // openGlViewer->setMinimumSize(QSize(50, 500));
  // openGlViewer->resize(10, 100);
  // openGlViewer->resize(500, 500);
  // layout = new QVBoxLayout();
  //[/unused]
  ui->setupUi(this);

  openGlViewer = new OpenGlViewer(_object);

  // ui->horizontalLayout->addWidget(openGlViewer);
  // ui->horizontalLayout->addItem(ui->horizontalLayout->takeAt(0));
  // qDebug() << "Width=" << this->width();
  // openGlViewer->sizePolicy().setVerticalPolicy(QSizePolicy::Policy::Expanding);
  openGlViewer->setFixedWidth(this->width() * 0.8);
  openGlViewer->setFixedHeight(this->height());
  ui->horizontalLayout->insertWidget(0, openGlViewer);

  // ui->horizontalLayout->insertItem(0, openGlViewer->layout());

  // ui->centralwidget->show();
  // mainLayout = new QHBoxLayout();
  // mainLayout->addWidget(openGlViewer);

  // ui->centralwidget->setLayout(mainLayout);
  // ui->centralwidget->show();
}

MainAppWindow::~MainAppWindow() { delete ui; }
