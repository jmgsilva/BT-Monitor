#include "graph_model.h"
#include <cmath>
#include <iostream>

GraphEdgeModel::GraphEdgeModel(std::shared_ptr<GraphNodeModel> source, std::shared_ptr<GraphNodeModel> dest) : source_node(source), dest_node(dest) {
    setZValue(-1);
}

QRectF GraphEdgeModel::boundingRect() const {
    return QRectF();
}

void GraphEdgeModel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    //Needed for the path
    QPainterPath path;
    QPointF startPos = source_node->pos();
    QPointF endPos = dest_node->pos();
    QLineF startToEndLine, aux;
    QPointF ctrlPoint;

    startToEndLine.setLine(startPos.x(), startPos.y(), endPos.x(), endPos.y());


    //Needed for the arrows
    qreal mid = 0.4;
    QPointF midPoint;
    QLineF line, mirroredLine;

    path.moveTo(startPos.x(), startPos.y());

    if(source_node->getName() > dest_node->getName()) {
        aux.setP1(startToEndLine.center());
        aux.setAngle(startToEndLine.angle()+90);
        aux.setLength(15);
        ctrlPoint = aux.p2();
    }
    else {
        aux.setP1(startToEndLine.center());
        aux.setAngle(startToEndLine.angle()+90);
        aux.setLength(15);
        ctrlPoint = aux.p2();
    }

    //Draw the path
    path.quadTo(ctrlPoint, endPos);
    painter->drawPath(path);

    painter->setPen(QPen(Qt::white, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    midPoint = path.pointAtPercent(mid);
    line.setP1(midPoint);
    line.setAngle(path.angleAtPercent(mid)+140);
    line.setLength(5);
    mirroredLine.setP1(midPoint);
    mirroredLine.setAngle(path.angleAtPercent(mid)-140);
    mirroredLine.setLength(5);
    painter->drawLine(line);
    painter->drawLine(mirroredLine);
}

//-10, -10 is the upper left corner of the rectangle and 20, 20 is its width and height. This way, it's (0,0) is in the center, which is what is desired
GraphNodeModel::GraphNodeModel(int x, int y, std::string node_name) : QGraphicsEllipseItem(-10, -10, 20, 20) {
    name = node_name;

    setPos(x, y);

    label = std::make_unique<QLabel>(QString::fromStdString(name));
    label->move(x, y);

    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::black);
    setPen(pen);

    QBrush brush;
    brush.setColor(Qt::white);
    brush.setStyle(Qt::SolidPattern);
    setBrush(brush);
}

void GraphNodeModel::updatePos(int x, int y) {
    setPos(x, y);
}

std::string GraphNodeModel::getName() {
    return name;
}

void GraphNodeModel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // Call the base class implementation of paint()
    QGraphicsEllipseItem::paint(painter, option, widget);

    // Use the painter to draw the label text inside the ellipse
    painter->drawText(rect(), Qt::AlignCenter, label->text());
}


Graph::Graph(std::string graph_string) {
    std::string source_node_name;
    std::string dest_node_name;
    int edge_distance;
    unsigned char ctrl_char;
    int start = 0;
    int end;
    x = 0;
    y = 0;


    if(graph_string.empty()) return;

    while(start < graph_string.length()) {
        ctrl_char = '0';
        end = graph_string.find("(", start);
        source_node_name = graph_string.substr(start, end - start);
        start = end+1;
        addNode(x, y, source_node_name);
        while(ctrl_char != ')') {
            end = graph_string.find_first_of(":)", start);
            ctrl_char = graph_string.at(end);
            if(ctrl_char == ':') {
                dest_node_name = graph_string.substr(start, end - start);
                start = end+1;
                end = graph_string.find_first_of(",)", start);
                ctrl_char = graph_string.at(end);
                edge_distance = std::stoi(graph_string.substr(start, end - start)); //not used yet
                addEdge(source_node_name, dest_node_name);
                start = end+1;
            }
            else start = end+1;
        }
    }
}

std::shared_ptr<GraphNodeModel> Graph::addNode(int x, int y, std::string node_name) {
    bool node_exists = false;
    std::shared_ptr<GraphNodeModel> node;

    for (auto it = begin(nodes); it != end(nodes); ++it) {
        std::string it_name = (*it)->getName();
        if(it_name == node_name) {
            node_exists = true;
            node = (*it);
        }
    }

    if(!node_exists) {
        node = std::make_shared<GraphNodeModel>(x, y, node_name);
        nodes.push_back(node);
        this->x += 60;
        this->y += 60;
    }

    return node;
}

std::vector<std::shared_ptr<GraphNodeModel>>& Graph::getGraphNodes() {
    return nodes;
}

std::vector<std::shared_ptr<GraphEdgeModel>>& Graph::getGraphEdges() {
    return edges;
}

void Graph::addEdge(std::string source_node_name, std::string dest_node_name) {
    bool source_node_found = false;
    bool dest_node_found = false;
    std::shared_ptr<GraphNodeModel> source_node;
    std::shared_ptr<GraphNodeModel> dest_node;


    //Check if the node named source_node already exists
    for (auto it = begin(nodes); it != end(nodes); ++it) {
        std::string it_name = (*it)->getName();
        if(it_name == source_node_name) {
            source_node_found = true;
            source_node = (*it);
        }
        else if(it_name == dest_node_name) {
            dest_node_found = true;
            dest_node = (*it);
        }
    }

    //If not, create them
    if(!source_node_found)
        source_node = addNode(x, y, source_node_name);
    if(!dest_node_found)
        dest_node = addNode(x, y, dest_node_name);

    //Create the edge
    edges.push_back(std::make_shared<GraphEdgeModel>(source_node, dest_node));
}
