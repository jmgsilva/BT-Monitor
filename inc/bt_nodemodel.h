#ifndef BT_NODEMODEL_H
#define BT_NODEMODEL_H

#include <QString>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

class NodeModel {
    std::string node_name;
    std::string node_type;

    int children_x_sum = 0;
    uint8_t children_count = 0;

    NodeModel* parent;

    //vertical layout contains the horizontal layout and the name_box
    //horizontal layout contains the node type' icon and the node type label
    std::unique_ptr<QFrame> node_frame;
    std::unique_ptr<QVBoxLayout> v_layout;
    std::unique_ptr<QHBoxLayout> h_layout;
    std::unique_ptr<QLabel> type_logo;
    std::unique_ptr<QLabel> type_box;
    std::unique_ptr<QLabel> name_box;

public:
    NodeModel(int x, int y, std::string type, std::string name);
    void setParent(NodeModel*);
    void updatePosition(int, uint8_t);
    void updateStylesheet(std::string node_status);
    const std::string& getName();
    NodeModel* getParent();
    QFrame* getNodeFrame();
};

#endif // BT_NODEMODEL_H
