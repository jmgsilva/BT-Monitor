#ifndef CONNECTIONMODEL_H
#define CONNECTIONMODEL_H

#include "nodemodel.h"
#include <QPainter>
#include <QGraphicsItem>

class NodeModel;

class ConnectionModel : public QGraphicsItem {
    NodeModel *source, *dest;

public:
    ConnectionModel(NodeModel *source, NodeModel *dest);

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // CONNECTIONMODEL_H
