#ifndef GRAPH_MODEL_H
#define GRAPH_MODEL_H

#include <QGraphicsEllipseItem>
#include <QLabel>
#include <QString>
#include <QPainter>
#include <QPainterPath>

class GraphNodeModel;

// Edge
class GraphEdgeModel : public QGraphicsItem {
    std::shared_ptr<GraphNodeModel> source_node;
    std::shared_ptr<GraphNodeModel> dest_node;

public:
    GraphEdgeModel(std::shared_ptr<GraphNodeModel> source, std::shared_ptr<GraphNodeModel> dest);

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

// Node
class GraphNodeModel : public QGraphicsEllipseItem {
    std::string name;
    std::unique_ptr<QLabel> label;

public:
    GraphNodeModel(int x, int y, std::string node_name);
    std::string getName();
    void updatePos(int x, int y);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

// Graph
class Graph {
    std::vector<std::shared_ptr<GraphNodeModel>> nodes;
    std::vector<std::shared_ptr<GraphEdgeModel>> edges;
    int x, y;

public:
    Graph(std::string graph_string);
    std::shared_ptr<GraphNodeModel> addNode(int x, int y, std::string node_name);
    void addEdge(std::string source_node_name, std::string dest_node_name);
    std::vector<std::shared_ptr<GraphNodeModel>>& getGraphNodes();
    std::vector<std::shared_ptr<GraphEdgeModel>>& getGraphEdges();
};

#endif // GRAPH_MODEL_H
