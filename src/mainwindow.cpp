#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "zmqpuller.h"
#include "graph_model.h"

//Zoom by scrolling
#include <QTimeLine>
#include <QWheelEvent>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setCentralWidget(ui->tabWidget);
}

void MainWindow::drawSomething() {
    graphicsviewBT = new MyQGraphicsView();
    sceneBT = new QGraphicsScene();
    sceneBT->setBackgroundBrush(Qt::darkGray);

    graphicsviewGraph = new QGraphicsView();
    sceneGraph = new QGraphicsScene();
    sceneGraph->setBackgroundBrush(Qt::darkGray);

    graphicsviewBT->setScene(sceneBT);
    ui->verticalLayout_5->addWidget(graphicsviewBT);
    graphicsviewBT->show();

    graphicsviewGraph->setScene(sceneGraph);
    ui->verticalLayout_6->addWidget(graphicsviewGraph);
    graphicsviewGraph->show();

    /*graph = std::make_unique<Graph>();
    graph->addEdge("A", "J");
    graph->addEdge("J", "K");
    graph->addEdge("K", "P");
    graph->addEdge("P", "Q");
    graph->addEdge("Q", "O");
    graph->addEdge("J", "K");
    graph->addEdge("O", "N");
    graph->addEdge("Q", "R");
    graph->addEdge("R", "M");
    graph->addEdge("M", "L");
    graph->addEdge("L", "K");
    graph->addEdge("K", "J");
    graph->addEdge("J", "I");
    graph->addEdge("I", "B");
    graph->addEdge("B", "C");
    graph->addEdge("C", "H");
    graph->addEdge("H", "G");
    graph->addEdge("G", "D");
    graph->addEdge("D", "E");
    graph->addEdge("E", "D");
    graph->addEdge("D", "G");
    graph->addEdge("G", "F");
    graph->addEdge("F", "M");
    graph->addEdge("M", "R");
    graph->addEdge("R", "Q");
    graph->addEdge("Q", "P");
    graph->addEdge("P", "K");
    graph->addEdge("K", "J");
    graph->addEdge("J", "A");


    int num_nodes = graph->getGraphNodes().size();
    double angle_step = 2 * M_PI / num_nodes;
    double current_angle = 0;
    double radius = num_nodes * 10;

    for (int i = 0; i < num_nodes; i++) {
        std::shared_ptr<GraphNodeModel> node = graph->getGraphNodes()[i];
        node->updatePos(radius * cos(current_angle), radius * sin(current_angle));
        current_angle += angle_step;
    }

    for (auto it = begin (graph->getGraphNodes()); it != end (graph->getGraphNodes()); ++it) {
        sceneGraph->addItem((*it).get());
    }

    for (auto it = begin (graph->getGraphEdges()); it != end (graph->getGraphEdges()); ++it) {
        sceneGraph->addItem((*it).get());
    }*/

    //ovo->moveBy(-40, -40);
}

void MainWindow::handleMessage(const std::string &message) {
    std::cout << message << std::endl;
    int header_end = message.find("=");
    std::string header = message.substr(0, header_end);
    std::string content = message.substr(header_end+1);
    if (header == "Status") {
        tree->updateNodesStatus(content);
        std::cout << message << std::endl;
    }
    else if (header == "Tree") {
        sceneBT->clear();
        sceneBT->update();
        graphicsviewBT->update();
        tree = std::make_unique<BehaviorTree>(content);
        tree->orderTree();
        for (auto it = begin (tree->getTreeNodes()); it != end (tree->getTreeNodes()); ++it) {
            sceneBT->addWidget((*it)->getNodeFrame());
        }
        for (auto it = begin (tree->getTreeConnections()); it != end (tree->getTreeConnections()); ++it) {
            sceneBT->addItem((*it));
        }
        //graphicsviewBT->fitInView(sceneBT->sceneRect(), Qt::KeepAspectRatio);
    }
    else if (header == "Graph") {
        graph = std::make_unique<Graph>(content);
        int num_nodes = graph->getGraphNodes().size();
        double angle_step = 2 * M_PI / num_nodes;
        double current_angle = 0;
        double radius = num_nodes * 10;

        for (int i = 0; i < num_nodes; i++) {
            std::shared_ptr<GraphNodeModel> node = graph->getGraphNodes()[i];
            node->updatePos(radius * cos(current_angle), radius * sin(current_angle));
            current_angle += angle_step;
        }

        for (auto it = begin (graph->getGraphNodes()); it != end (graph->getGraphNodes()); ++it) {
            sceneGraph->addItem((*it).get());
        }

        for (auto it = begin (graph->getGraphEdges()); it != end (graph->getGraphEdges()); ++it) {
            sceneGraph->addItem((*it).get());
        }
        graphicsviewGraph->fitInView(sceneGraph->sceneRect(), Qt::KeepAspectRatio);
    }
    else throw std::logic_error("Unknown type of message received");
}

void MainWindow::on_pushButton_clicked() {
    ui->pushButton->setDisabled(1);
    ui->port_lineEdit->setDisabled(1);
    ui->pushButton->setText("Server is running");
    ui->pushButton->setStyleSheet("color: rgb(94, 92, 100);");
    ZMQPuller *zmq_server = new ZMQPuller(ui->ip_lineEdit->text().toStdString(), ui->port_lineEdit->text().toStdString());
    zmq_server->moveToThread(&th);
    connect(zmq_server, &QThread::finished, zmq_server, &QObject::deleteLater);
    connect(zmq_server, &ZMQPuller::messageReceived, this, &MainWindow::handleMessage);
    zmq_server->start();
}

void MainWindow::on_pushButton_2_clicked() {
    close();
}

void MyQGraphicsView::wheelEvent ( QWheelEvent * event ) {
    int numDegrees = event->angleDelta().y() / 8;
    int numSteps = numDegrees / 15; // see QWheelEvent documentation
    _numScheduledScalings += numSteps;
    if (_numScheduledScalings * numSteps < 0) // if user moved the wheel in another direction, we reset previously scheduled scalings
    _numScheduledScalings = numSteps;
    QTimeLine *anim = new QTimeLine(350, this);
    anim->setUpdateInterval(20);
    connect(anim, SIGNAL (valueChanged(qreal)), SLOT (scalingTime(qreal)));
    connect(anim, SIGNAL (finished()), SLOT (animFinished()));
    anim->start();
}

void MyQGraphicsView::scalingTime(qreal x) {
    qreal factor = 1.0+ qreal(_numScheduledScalings) / 300.0;
    scale(factor, factor);
}

void MyQGraphicsView::animFinished() {

    if (_numScheduledScalings > 0)
        _numScheduledScalings--;
    else
        _numScheduledScalings++;
    sender()->~QObject();
}

MainWindow::~MainWindow() {
    th.quit();
    th.wait();
    delete ui;
}

