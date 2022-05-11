#ifndef NODEMODEL_H
#define NODEMODEL_H

#include "connectionmodel.h"
#include <QGraphicsItem>
#include <QString>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSvgWidget>

class ConnectionModel;

class NodeModel {
    int pos_x;
    int pos_y;
    int pos_x_bckp;
    int number_of_children;
    int children_x_sum;
    std::string node_type;
    std::string node_name;

    NodeModel* parent;
    ConnectionModel* connection_to_parent;

    //vertical layout contains the horizontal layout and the name_box
    //horizontal layout contains the node type' icon and the node type label
    QFrame* node_frame;
    QVBoxLayout* v_layout;
    QHBoxLayout* h_layout;

    QLabel* node_type_logo;
    QLabel* type_box;
    QLabel* name_box;


public:
    NodeModel(int x, int y, std::string type, std::string name);
    NodeModel(int x, int y, std::string type, std::string name, NodeModel* parent);
    void setX(int new_x);
    void setParent(NodeModel* parent);
    void setConnection(ConnectionModel *connection);
    void updateLimits(int child_x);
    void moveHorizontally();
    void updateStylesheet(std::string node_status);
    int getX();
    std::string getName();
    NodeModel* getParent();
    ConnectionModel* getConnectionToParent();
    QFrame* getNodeFrame();
};

#endif // NODEMODEL_H
