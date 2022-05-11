#ifndef UTILS_H
#define UTILS_H

#include "nodemodel.h"
#include <vector>
#include <string>


extern std::vector<NodeModel*> tree_nodes;
extern std::vector<ConnectionModel*> connections;

void getBehaviorTreeFromString(std::string tree);
void orderTree();
void getNodeStatus(std::string message);

#endif // UTILS_H
