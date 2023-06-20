#ifndef BT_MODEL_H
#define BT_MODEL_H

#include "bt_nodemodel.h"
#include "bt_connectionmodel.h"

class BTModel {
    std::vector<std::unique_ptr<NodeModel>> tree_nodes;
    std::vector<std::unique_ptr<ConnectionModel>> tree_connections;

public:
    BTModel(std::string tree);
    void orderTree();
    void updateNodesStatus(std::string message);
    const std::vector<std::unique_ptr<NodeModel>>& getTreeNodes();
    const std::vector<std::unique_ptr<ConnectionModel>>& getTreeConnections();
};

#endif // BT_MODEL_H
