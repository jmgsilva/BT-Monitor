#include "bt_model.h"
#include <iostream>

BehaviorTree::BehaviorTree(std::string tree) {
    std::vector<int> parent_idxs_stack;
    std::string node_type;
    std::string node_name;
    int start = 0;
    int end = tree.find(":");
    int vector_idx = 0;
    int x = 0;
    int y = 0;

    //This block of code adds the first node of the tree (the first parent for the subsequent nodes).
    //The while cycle is done taking in account this added first node on the behaveior tree's received string. Otherwise, it doesn't work.
    node_type = tree.substr(start, end - start);
    //std::cout << node_type << std::endl;
    start = end+1;
    end = tree.find("(", start);
    node_name = tree.substr(start, end-start);
    start = end+1;
    //std::cout << node_name << std::endl;
    tree_nodes.push_back(new NodeModel(x, y, node_type, node_name));
    //std::cout << std::to_string(vector_idx) << std::endl;
    vector_idx++;

    /*tree_nodes.push_back(new NodeModel(x, y, "Root", "Root"));
    vector_idx++;
    y += 150;*/

    unsigned char ctrl_char;

    while(start < tree.length()) {
        ctrl_char = tree.at(end);
        //std::cout << ctrl_char << std::endl;
        if(ctrl_char == ')') {
            start++;
            end++;
            parent_idxs_stack.pop_back();
            y -= 150;
        }
        else {
            end = tree.find(":", start);
            node_type = tree.substr(start, end - start);
            //std::cout << node_type << std::endl;
            start = end+1;
            end = tree.find_first_of("(),", start);
            node_name = tree.substr(start, end-start);
            //std::cout << node_name << std::endl;
            start = end+1;
            if(ctrl_char == '(') {
                parent_idxs_stack.push_back(vector_idx-1);
                y += 150;
                tree_nodes.push_back(new NodeModel(x, y, node_type, node_name));
                tree_nodes[vector_idx]->setParent(tree_nodes[parent_idxs_stack.back()]);
                tree_connections.push_back(new ConnectionModel(tree_nodes[parent_idxs_stack.back()]->getNodeFrame(), tree_nodes[vector_idx]->getNodeFrame()));
                /*std::cout << std::to_string(parent_idxs_stack.back()) << std::endl;
                std::cout << std::to_string(vector_it) << std::endl;*/
                vector_idx++;
            }
            else if (ctrl_char == ',') {
                x += 150;
                tree_nodes.push_back(new NodeModel(x, y, node_type, node_name));
                tree_nodes[vector_idx]->setParent(tree_nodes[parent_idxs_stack.back()]);
                tree_connections.push_back(new ConnectionModel(tree_nodes[parent_idxs_stack.back()]->getNodeFrame(), tree_nodes[vector_idx]->getNodeFrame()));
                /*std::cout << std::to_string(parent_idxs_stack.back()) << std::endl;
                std::cout << std::to_string(vector_it) << std::endl;*/
                vector_idx++;
            }
        }
    }
}

void BehaviorTree::orderTree() {
    uint8_t children_count = 0;
    int children_x_sum = 0;
    NodeModel* it_parent = tree_nodes[tree_nodes.size()-1];

    for (int i = tree_nodes.size()-1; i >= 1; i--) {
        NodeModel* it_node = tree_nodes[i];
        NodeModel* it_node_parent = it_node->getParent();
        if(it_node_parent->getName() != it_parent->getName()) {
            it_parent->updateLimits(children_x_sum, children_count);
            it_parent = it_node_parent;
            children_count = 0;
            children_x_sum = 0;
        }

        children_count++;
        children_x_sum += it_node->getX();
    }

    tree_nodes[0]->updateLimits(tree_nodes[1]->getX(), 1);

    for(auto it : tree_nodes) {
        it->moveHorizontally();
    }
}

void BehaviorTree::updateNodesStatus(std::string message) {
    std::string node_name;
    std::string node_status;
    int start = 0;
    int end = 0;
    while(message.at(end) != '/') {
        end = message.find(":", start);
        node_name = message.substr(start, end-start);
        start = end+1;
        end = message.find_first_of(",/", start);
        node_status = message.substr(start, end-start);
        start = end+1;
        for(auto it : tree_nodes) {
            if(it->getName() == node_name)
                it->updateStylesheet(node_status);
        }
    }
}

std::vector<NodeModel*>& BehaviorTree::getTreeNodes() {
    return tree_nodes;
}

std::vector<ConnectionModel*>& BehaviorTree::getTreeConnections() {
    return tree_connections;
}
