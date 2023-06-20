#include "bt_model.h"
#include <iostream>

BTModel::BTModel(std::string tree) {
    std::vector<int> parent_idxs_stack;
    std::string node_type;
    std::string node_name;
    int start = 0, x = 0, y = 0;
    int end = tree.find(":");
    unsigned char ctrl_char;

    //Create the Root node
    node_type = tree.substr(start, end - start);
    start = end+1;
    end = tree.find("(", start);
    node_name = tree.substr(start, end-start);
    start = end+1;
    tree_nodes.push_back(std::make_unique<NodeModel>(x, y, node_type, node_name));

    //While the string is not over
    while(start < tree.length()) {
        ctrl_char = tree.at(end);

        //If the children of a node ended, retreat one level in the hierarchy
        if(ctrl_char == ')') {
            start++;
            end++;
            parent_idxs_stack.pop_back();
            y -= 175;
        }

        else {
            //Get type and name of the new node
            end = tree.find(":", start);
            node_type = tree.substr(start, end - start);
            start = end+1;
            end = tree.find_first_of("(),", start);
            node_name = tree.substr(start, end-start);
            start = end+1;

            //If the new node has children, advance one level in the hierarchy
            if(ctrl_char == '(') {
                parent_idxs_stack.push_back(tree_nodes.size()-1);
                y += 175;
            }
            //If the next node is from the same level in the hierarchy, increment x
            else if (ctrl_char == ',')
                x += 200;
            //Create new node, set its parent and add the connection from the node to its parent
            tree_nodes.push_back(std::make_unique<NodeModel>(x, y, node_type, node_name));
            tree_nodes.back()->setParent(tree_nodes[parent_idxs_stack.back()].get());
            tree_connections.push_back(std::make_unique<ConnectionModel>(tree_nodes[parent_idxs_stack.back()]->getNodeFrame(), tree_nodes.back()->getNodeFrame()));
        }
    }
}

void BTModel::orderTree() {
    uint8_t children_count = 0;
    int children_x_sum = 0;
    NodeModel* it_parent = tree_nodes[tree_nodes.size()-1].get();

    for (int i = tree_nodes.size()-1; i > 0; i--) {
        NodeModel* it_node = tree_nodes[i].get();
        NodeModel* it_node_parent = it_node->getParent();
        std::cout << "Name: " << it_node->getName() << std::endl;
        if(it_node_parent->getName() != it_parent->getName()) {
            it_parent->updatePosition(children_x_sum, children_count);
            it_parent = it_node_parent;
            children_count = 0;
            children_x_sum = 0;
        }

        children_count++;
        children_x_sum += it_node->getNodeFrame()->pos().x();
    }

    //to correct the position of the Root node
    tree_nodes[0]->updatePosition(tree_nodes[1]->getNodeFrame()->pos().x(), 1);
}

void BTModel::updateNodesStatus(std::string message) {
    std::string node_name;
    std::string node_status;
    int start = 0, end = 0;

    while(message.at(end) != '/') {
        //Get name of the node
        end = message.find(":", start);
        node_name = message.substr(start, end-start);
        start = end+1;

        //Get new status of the node
        end = message.find_first_of(",/", start);
        node_status = message.substr(start, end-start);
        start = end+1;

        //Search for the node and update its stylesheet
        for(int i = 0; i < tree_nodes.size()-1; ++i) {
            if(tree_nodes[i]->getName() == node_name)
                tree_nodes[i]->updateStylesheet(node_status);
        }
    }
}

const std::vector<std::unique_ptr<NodeModel>>& BTModel::getTreeNodes() {
    return tree_nodes;
}

const std::vector<std::unique_ptr<ConnectionModel>>& BTModel::getTreeConnections() {
    return tree_connections;
}
