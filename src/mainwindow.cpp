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
    //Instantiate BT view and scene
    graphics_view_BT = new MyQGraphicsView();
    graphics_scene_BT = new QGraphicsScene();
    graphics_scene_BT->setBackgroundBrush(Qt::darkGray);

    //Instantiate Graph view and scene
    graphicsviewGraph = new QGraphicsView();
    sceneGraph = new QGraphicsScene();
    sceneGraph->setBackgroundBrush(Qt::darkGray);

    //Assign the BT scene to the BT view
    graphics_view_BT->setScene(graphics_scene_BT);

    //Assign the BT view to the BT vertical layout of the ui and display it
    ui->verticalLayout_5->addWidget(graphics_view_BT);
    graphics_view_BT->show();

    //Assign the Graph scene to the BT view
    graphicsviewGraph->setScene(sceneGraph);

    //Assign the Graph view to the BT vertical layout of the ui and display it
    ui->verticalLayout_6->addWidget(graphicsviewGraph);
    graphicsviewGraph->show();
}

void MainWindow::handleMessage(const std::string &message) {
    int header_end = message.find("=");
    std::string header = message.substr(0, header_end);
    std::string content = message.substr(header_end+1);
    std::cout << message << std::endl;
    if (header == "Status") {
        tree->updateNodesStatus(content);
    }
    else if (header == "Tree") {
        tree = std::make_unique<BTModel>(content);
        tree->orderTree();
        for(auto& it : tree->getTreeNodes())
            graphics_scene_BT->addWidget(it->getNodeFrame());
        for(auto& it : tree->getTreeConnections())
            graphics_scene_BT->addItem(it.get());
        graphics_scene_BT->update();
        graphics_view_BT->fitInView(graphics_scene_BT->sceneRect(), Qt::KeepAspectRatio);
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

void MainWindow::on_ZMQ_pushButton_clicked() {
    ZMQPuller *zmq_puller;

    //Disable the "Setup ZMQ Puller" QPushButton and the port QLineEdit
    ui->ZMQ_pushButton->setDisabled(1);
    ui->port_lineEdit->setDisabled(1);

    //Change the appearence of the button
    ui->ZMQ_pushButton->setText("Binded");
    ui->ZMQ_pushButton->setStyleSheet("color: rgb(94, 92, 100);");

    //Setup ZeroMQ Puller
    zmq_puller = new ZMQPuller(ui->port_lineEdit->text().toStdString());
    zmq_puller->moveToThread(&th);
    connect(zmq_puller, &QThread::finished, zmq_puller, &QObject::deleteLater);
    connect(zmq_puller, &ZMQPuller::messageReceived, this, &MainWindow::handleMessage);
    zmq_puller->start();
}

void MainWindow::on_exit_pushButton_clicked() {
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
