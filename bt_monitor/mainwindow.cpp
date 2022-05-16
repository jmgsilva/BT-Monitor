#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "nodemodel.h"
#include "connectionmodel.h"
#include "utils.h"
#include "zmqserver.h"
#include <QGraphicsView>
#include <stdexcept>

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::drawSomething() {
    scene = new QGraphicsScene();
    scene->setBackgroundBrush(Qt::darkGray);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

void MainWindow::handleMessage(const std::string &message) {
    //Tree=Fallback:fb1...
    //Status=fb1:success...
    int header_end = message.find("=");
    std::string header = message.substr(0, header_end);
    std::string content = message.substr(header_end+1);
    std::cout << content << std::endl;
    if(header == "Tree") {
        getBehaviorTreeFromString(content);
        orderTree();
        for (auto it = begin (tree_nodes); it != end (tree_nodes); ++it) {
            scene->addWidget((*it)->getNodeFrame());
        }

        for (auto it = begin (connections); it != end (connections); ++it) {
            scene->addItem((*it));
        }
        //ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    }
    else if (header == "Status") {
        getNodeStatus(content);
    }
    //else throw std::logic_error("Unknown type of message received");
}

void MainWindow::on_pushButton_clicked()
{
    ui->pushButton->setDisabled(1);
    ui->pushButton->setText("Server is running");
    ZMQServer *zmq_server = new ZMQServer();
    zmq_server->moveToThread(&th);
    connect(zmq_server, &QThread::finished, zmq_server, &QObject::deleteLater);
    connect(zmq_server, &ZMQServer::messageReceived, this, &MainWindow::handleMessage);
    zmq_server->start();
}

void MainWindow::on_pushButton_2_clicked()
{
    close();
}

MainWindow::~MainWindow()
{
    th.quit();
    th.wait();
    delete ui;
}

