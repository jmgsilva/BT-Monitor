#ifndef BT_CONNECTIONMODEL_H
#define BT_CONNECTIONMODEL_H

#include <QPainter>
#include <QGraphicsItem>
#include <QFrame>

class ConnectionModel : public QGraphicsItem {
    QFrame *source_node, *dest_node;

public:
    ConnectionModel(QFrame *source_node, QFrame *dest_node);

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // BT_CONNECTIONMODEL_H
