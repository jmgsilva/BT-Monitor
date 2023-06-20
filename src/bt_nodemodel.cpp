#include "bt_nodemodel.h"
#include <iostream>

NodeModel::NodeModel(int x, int y, std::string type, std::string name) : node_type(type), node_name(name) {
    node_frame = std::make_unique<QFrame>();
    v_layout = std::make_unique<QVBoxLayout>();
    h_layout = std::make_unique<QHBoxLayout>();
    type_logo = std::make_unique<QLabel>();
    type_box = std::make_unique<QLabel>();
    name_box = std::make_unique<QLabel>();
    QString svg_path;
    QFont font;

    //Move position of the frame to the specified coordinates and change its appearance
    node_frame->move(x,y);
    node_frame->setFrameStyle(QFrame::Panel | QFrame::Plain);
    node_frame->setLineWidth(2);
    node_frame->setStyleSheet("color: white;" "background-color: lightGray;");
    node_frame->setFixedWidth(175);
    //Set the vertical layout as the layout of the frame
    node_frame->setLayout(v_layout.get());

    //Find the matching logo taking into account the type of the node and add it to the horizontal layout
    svg_path = ":/" + QString::fromStdString(type) + ".svg";
    type_logo->setPixmap(QPixmap(svg_path.toLower()).scaledToHeight(20));
    h_layout->addWidget(type_logo.get(), 0, Qt::AlignRight);

    //Add the horizontal layout to the vertical layout, center it and add a spacing
    v_layout->addLayout(h_layout.get());
    v_layout->setAlignment(h_layout.get(), Qt::AlignHCenter);
    v_layout->addSpacing(5);

    //Add the type string to its respective label and add the label to the horizontal layout
    type_box->setText(QString::fromStdString(type));
    type_box->setStyleSheet("color: black");
    h_layout->addWidget(type_box.get(), 0, Qt::AlignLeft);
    //Change the font used for the type label
    font.setBold(true);
    font.setPointSize(13);
    type_box->setFont(font);

    //Add the name string to its respective label and add the label to the vertical layout
    name_box->setText(QString::fromStdString(name));
    name_box->setStyleSheet("color: black");
    v_layout->addWidget(name_box.get(), 0, Qt::AlignCenter);
}


void NodeModel::updatePosition(int children_x_sum, uint8_t children_count) {
    if(children_count == 0)
        return;
    this->children_count += children_count;
    this->children_x_sum += children_x_sum;
    //Calculate new x-coordinate and move frame
    node_frame->move(this->children_x_sum/this->children_count, getNodeFrame()->pos().y());
}

void NodeModel::updateStylesheet(std::string node_status) {
    if(node_status == "Success") //Change background color of the node to green
        node_frame->setStyleSheet("background-color: rgb(217, 255, 219);");
    else if(node_status == "Failure") //Change background color of the node to red
        node_frame->setStyleSheet("background-color: rgb(255, 223, 223);");
    else if(node_status == "Running") //Change background color of the node to blue
        node_frame->setStyleSheet("background-color: rgb(204, 229, 255);");
    else if(node_status == "Idle") //Change background color of the node to gray
        node_frame->setStyleSheet("background-color: lightGray;");
}

void NodeModel::setParent(NodeModel* parent) {
    this->parent = parent;
}

const std::string& NodeModel::getName() {
    return node_name;
}

NodeModel* NodeModel::getParent() {
    return parent;
}

QFrame* NodeModel::getNodeFrame() {
    return node_frame.get();
}
