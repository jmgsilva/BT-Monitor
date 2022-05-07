#include "nodemodel.h"

NodeModel::NodeModel(int x, int y, QString type, QString name) {
    pos_x = x;
    pos_y = y;
    node_type = type;
    node_name = name;

    v_layout = new QVBoxLayout();
    h_layout = new QHBoxLayout();

    node_frame = new QFrame();
    node_frame->setFrameStyle(QFrame::Panel | QFrame::Plain);
    node_frame->setStyleSheet("background-color: lightGray");
    node_frame->setLayout(v_layout);

    node_type_logo = new QLabel();
    type_box = new QLabel();
    name_box = new QLabel();

    QString svgPath = ":/" + type + ".svg";
    node_type_logo->setPixmap(QPixmap(svgPath.toLower()).scaledToHeight(20));
    h_layout->addWidget(node_type_logo, 0, Qt::AlignLeft);

    v_layout->addLayout(h_layout);
    v_layout->addSpacing(5);
    v_layout->addWidget(name_box);

    type_box->setText(type);
    type_box->setStyleSheet("color : black");
    QFont font;
    font.setBold(true);
    font.setPointSize(13);
    type_box->setFont(font);
    h_layout->addWidget(type_box, 0, Qt::AlignRight);
    type_box->setFixedHeight(20);

    name_box->setText(name);
    name_box->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    v_layout->addWidget(name_box, 0, Qt::AlignCenter);

    node_frame->setGeometry(x, y, 50, 50);
}

QFrame* NodeModel::getNodeFrame() {
    return node_frame;
}

