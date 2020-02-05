#include "headers/mainappwindow.h"
#include "ui_mainappwindow.h"

#include <QLabel>

MainAppWindow::MainAppWindow(object3d _object, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainAppWindow)
{
    //[unused]
    // openGlViewer->setMinimumSize(QSize(50, 500));
    // openGlViewer->resize(10, 100);
    // openGlViewer->resize(500, 500);
    // layout = new QVBoxLayout();
    //[/unused]
    ui->setupUi(this);

    openGlViewer = new OpenGlViewer(_object);

    mainLayout = new QHBoxLayout();
    mainLayout->addWidget(openGlViewer);

    ui->centralwidget->setLayout(mainLayout);
    ui->centralwidget->show();
}

MainAppWindow::~MainAppWindow()
{
    delete ui;
}
