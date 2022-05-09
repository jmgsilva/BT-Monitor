#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "nodemodel.h"
#include "connectionmodel.h"
#include <QGraphicsView>
#include <QGraphicsScene>

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::drawSomething() {
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setBackgroundBrush(Qt::darkGray);

    NodeModel *node1 = new NodeModel(0, 0, "Fallback", "Fallback1");
    NodeModel *node2 = new NodeModel(0, 300, "Sequence", "Sequence1");

    std::cout << node1->getNodeFrame()->width() << std::endl;

    scene->addWidget(node1->getNodeFrame());
    scene->addWidget(node2->getNodeFrame());
    scene->addItem(new ConnectionModel(node1, node2));

    NodeModel *parent = node2->getParent();

    std::cout << parent->getName().toStdString() << std::endl;

    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    //ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

MainWindow::~MainWindow()
{
    delete ui;
}
