#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "nodemodel.h"
#include "connectionmodel.h"
#include "utils.h"
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

    //NodeModel *node1 = new NodeModel(0, 0, "Fallback", "Fallback1");
    //NodeModel *node2 = new NodeModel(0, 300, "Sequence", "Sequence1");

    //std::cout << node1->getNodeFrame()->width() << std::endl;

    /*scene->addWidget(node1->getNodeFrame());
    scene->addWidget(node2->getNodeFrame());
    scene->addItem(new ConnectionModel(node1, node2));*/

    for (auto it = begin (tree_nodes); it != end (tree_nodes); ++it) {
        scene->addWidget((*it)->getNodeFrame());
    }

    for (auto it = begin (connections); it != end (connections); ++it) {
        scene->addItem((*it));
    }

    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

    //getNodeStatus("fb1:success,a1:failure/");
}

MainWindow::~MainWindow()
{
    delete ui;
}
