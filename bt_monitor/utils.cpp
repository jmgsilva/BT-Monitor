#include "utils.h"

#include <iostream>

std::vector<NodeModel*> tree_nodes;
std::vector<ConnectionModel*> connections;

void getBehaviorTreeFromString(std::string tree) {
    std::vector<int> parent_idxs_stack;
    std::string node_type;
    std::string node_name;
    int start = 0;
    int end = tree.find(":");
    int vector_it = 0;
    int x = 0;
    int y = 0;
    int max_x = 0;

    node_type = tree.substr(start, end - start);
    //std::cout << node_type << std::endl;
    start = end+1;
    end = tree.find("(", start);
    node_name = tree.substr(start, end-start);
    start = end+1;
    //std::cout << node_name << std::endl;
    tree_nodes.push_back(new NodeModel(x, y, QString::fromStdString(node_type), QString::fromStdString(node_name)));
    //std::cout << std::to_string(vector_it) << std::endl;
    vector_it++;

    while(tree.at(start) != '/') {
        unsigned char ctrl_char = tree.at(end);
        //std::cout << ctrl_char << std::endl;
        if(ctrl_char == ')') {
            start++;
            end++;
            parent_idxs_stack.pop_back();
            y = y-100;
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
                parent_idxs_stack.push_back(vector_it-1);
                y = y+100;
                tree_nodes.push_back(new NodeModel(x, y, QString::fromStdString(node_type), QString::fromStdString(node_name)));
                tree_nodes[vector_it]->setParent(tree_nodes[parent_idxs_stack.back()]);
                connections.push_back(new ConnectionModel(tree_nodes[parent_idxs_stack.back()], tree_nodes[vector_it]));
                /*std::cout << std::to_string(parent_idxs_stack.back()) << std::endl;
                std::cout << std::to_string(vector_it) << std::endl;*/
                vector_it++;
            }
            else if (ctrl_char == ',') {
                x = x+150;
                tree_nodes.push_back(new NodeModel(x, y, QString::fromStdString(node_type), QString::fromStdString(node_name)));
                tree_nodes[vector_it]->setParent(tree_nodes[parent_idxs_stack.back()]);
                connections.push_back(new ConnectionModel(tree_nodes[parent_idxs_stack.back()], tree_nodes[vector_it]));
                /*std::cout << std::to_string(parent_idxs_stack.back()) << std::endl;
                std::cout << std::to_string(vector_it) << std::endl;*/
                vector_it++;
            }
        }
    }
}

void orderTree() {
    for (int i = tree_nodes.size()-1; i >= 1; i--) {
        NodeModel* node = tree_nodes[i];
        int x = node->getX();
        node->getParent()->updateLimits(x);
    }

    for (int i = 0; i <= tree_nodes.size()-1; i++) {
        tree_nodes[i]->moveHorizontally();
    }
}
