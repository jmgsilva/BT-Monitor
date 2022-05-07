#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "nodemodel.h"
#include <QObject>
#include <QLabel>
#include <QFile>
#include <QLineEdit>
#include <QFormLayout>
#include <QEvent>
#include <QGraphicsView>
#include <QGraphicsScene>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::drawSomething() {
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setBackgroundBrush(Qt::white);

    NodeModel node1(0, 0, "Fallback", "FB1");

    scene->addWidget(node1.getNodeFrame());

    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    //ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

MainWindow::~MainWindow()
{
    delete ui;
}
