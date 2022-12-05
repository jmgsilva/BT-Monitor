#ifndef BT_MODEL_H
#define BT_MODEL_H

#include "bt_nodemodel.h"
#include "bt_connectionmodel.h"

class BehaviorTree {
    std::vector<NodeModel*> tree_nodes;
    std::vector<ConnectionModel*> tree_connections;

public:
    BehaviorTree(std::string tree);
    void orderTree();
    void updateNodesStatus(std::string message);
    std::vector<NodeModel*>& getTreeNodes();
    std::vector<ConnectionModel*>& getTreeConnections();
};

#endif // BT_MODEL_H
