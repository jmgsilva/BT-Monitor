#ifndef BT_NODEMODEL_H
#define BT_NODEMODEL_H

#include <QString>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

class NodeModel {
    int pos_x;
    int pos_y;
    int pos_x_bckp;
    uint8_t children_count;
    int children_x_sum;
    std::string node_type;
    std::string node_name;

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
    NodeModel(int x, int y, std::string type, std::string name);
    NodeModel(int x, int y, std::string type, std::string name, NodeModel* parent);
    void setX(int new_x);
    void setParent(NodeModel*);
    void updateLimits(int, uint8_t);
    void moveHorizontally();
    void updateStylesheet(std::string node_status);
    int getX();
    std::string getName();
    NodeModel* getParent();
    QFrame* getNodeFrame();
};

#endif // BT_NODEMODEL_H
