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
    QString node_type;
    QString node_name;

    ConnectionModel* connection_to_parent;
    NodeModel* parent;

    //vertical layout contains the horizontal layout and the name_box
    //horizontal layout contains the node type' icon and the node type label
    QFrame* node_frame;
    QVBoxLayout* v_layout;
    QHBoxLayout* h_layout;

    QLabel* node_type_logo;
    QLabel* type_box;
    QLabel* name_box;


public:
    NodeModel(int x, int y, QString type, QString name);
    NodeModel(int x, int y, QString type, QString name, NodeModel* parent);
    void setParent(NodeModel* parent);
    void setConnection(ConnectionModel *connection);
    QString getName();
    NodeModel* getParent();
    ConnectionModel* getConnectionToParent();
    QFrame* getNodeFrame();
};

#endif // NODEMODEL_H
