#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "zmqpuller.h"

//Zoom by scrolling
#include <QTimeLine>
#include <QWheelEvent>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
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
        tree->updateNodesStatus(content);
    }
    else if (header == "Tree") {
        tree = new BehaviorTree(content);
        tree->orderTree();
        for (auto it = begin (tree->getTreeNodes()); it != end (tree->getTreeNodes()); ++it) {
            scene->addWidget((*it)->getNodeFrame());
        }
        for (auto it = begin (tree->getTreeConnections()); it != end (tree->getTreeConnections()); ++it) {
            scene->addItem((*it));
        }
        //ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
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

