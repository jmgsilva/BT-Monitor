#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "nodemodel.h"
#include "connectionmodel.h"
#include "utils.h"
#include "zmqserver.h"
#include <QGraphicsView>
#include <QTimeLine>
#include <QWheelEvent>
#include <stdexcept>

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::drawSomething() {
    graphicsview = new MyQGraphicsView();
    scene = new QGraphicsScene();
    scene->setBackgroundBrush(Qt::darkGray);

    graphicsview->setScene(scene);
    ui->verticalLayout->addWidget(graphicsview);
    graphicsview->show();
}

void MainWindow::handleMessage(const std::string &message) {
    int header_end = message.find("=");
    std::string header = message.substr(0, header_end);
    std::string content = message.substr(header_end+1);
    if (header == "Status") {
        getNodeStatus(content);
    }
    else if (header == "Tree") {
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
    else throw std::logic_error("Unknown type of message received");
}

void MainWindow::on_pushButton_clicked()
{
    ui->pushButton->setDisabled(1);
    ui->ip_lineEdit->setDisabled(1);
    ui->port_lineEdit->setDisabled(1);
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

MainWindow::~MainWindow()
{
    th.quit();
    th.wait();
    delete ui;
}

