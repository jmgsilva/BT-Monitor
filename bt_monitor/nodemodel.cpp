#include "nodemodel.h"
#include <iostream>

NodeModel::NodeModel(int x, int y, std::string type, std::string name) {
    parent = nullptr;
    pos_x = x;
    pos_y = y;
    pos_x_bckp = -60000;
    number_of_children = 0;
    children_x_sum = 0;
    node_type = type;
    node_name = name;

    v_layout = new QVBoxLayout();
    h_layout = new QHBoxLayout();

    node_frame = new QFrame();
    node_frame->move(x,y);
    node_frame->setFrameStyle(QFrame::Panel | QFrame::Plain);
    node_frame->setLineWidth(2);
    node_frame->setStyleSheet("color: white;" "background-color: lightGray;");
    node_frame->setLayout(v_layout);
    node_frame->setFixedWidth(142);

    node_type_logo = new QLabel();
    type_box = new QLabel();
    name_box = new QLabel();

    QString svgPath = ":/" + QString::fromStdString(type) + ".svg";
    node_type_logo->setPixmap(QPixmap(svgPath.toLower()).scaledToHeight(20));
    h_layout->addWidget(node_type_logo, 0, Qt::AlignRight);

    v_layout->addLayout(h_layout);
    v_layout->setAlignment(h_layout, Qt::AlignHCenter);
    v_layout->addSpacing(5);
    v_layout->addWidget(name_box);

    type_box->setText(QString::fromStdString(type));
    type_box->setStyleSheet("color: black");
    QFont font;
    font.setBold(true);
    font.setPointSize(13);
    type_box->setFont(font);
    h_layout->addWidget(type_box, 0, Qt::AlignLeft);

    name_box->setText(QString::fromStdString(name));
    //name_box->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    name_box->setStyleSheet("color: black");
    v_layout->addWidget(name_box, 0, Qt::AlignCenter);
}

void NodeModel::updateLimits(int x) {
    if(pos_x_bckp == -60000) {
        pos_x_bckp = pos_x;
    }
    number_of_children++;
    children_x_sum += x;
    //std::cout << std::to_string(pos_x) << std::endl;
    //std::cout << std::to_string(max_child_x) << std::endl;
    //std::cout << std::to_string(min_child_x) << std::endl;
    pos_x = children_x_sum/number_of_children;
    //std::cout << node_name << " " << std::to_string(pos_x) << std::endl;
}

void NodeModel::moveHorizontally() {
    node_frame->move(pos_x, pos_y);
}

void NodeModel::updateStylesheet(std::string node_status) {
    node_frame->setStyleSheet("");
    if(node_status == "success")
        node_frame->setStyleSheet("color: white;" "background-color: rgb(217, 255, 219);");
    else if(node_status == "failure")
        node_frame->setStyleSheet("color: white;" "background-color: rgb(255, 223, 223);");
    else if(node_status == "running")
        node_frame->setStyleSheet("color: white;" "background-color: rgb(204, 229, 255);");
    else if(node_status == "idle")
        node_frame->setStyleSheet("color: white;" "background-color: lightGray;");
}

void NodeModel::setX(int new_x){
    pos_x = new_x;
}

void NodeModel::setParent(NodeModel* parent) {
    this->parent = parent;
}

void NodeModel::setConnection(ConnectionModel* connection) {
    this->connection_to_parent = connection;
}

int NodeModel::getX() {
    return pos_x;
}

std::string NodeModel::getName() {
    return node_name;
}

NodeModel* NodeModel::getParent() {
    return parent;
}

ConnectionModel* NodeModel::getConnectionToParent() {
    return connection_to_parent;
}

QFrame* NodeModel::getNodeFrame() {
    return node_frame;
}
