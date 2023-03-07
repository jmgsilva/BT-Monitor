#include "bt_connectionmodel.h"

ConnectionModel::ConnectionModel(QFrame *source_node, QFrame *dest_node) : source_node(source_node), dest_node(dest_node) {}

QRectF ConnectionModel::boundingRect() const {
    return QRectF();
}

void ConnectionModel::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPoint sourcePoint(source_node->geometry().x()+(source_node->geometry().width()/2), source_node->geometry().y()+(source_node->geometry().height()));
    QPoint destPoint(dest_node->geometry().x()+(dest_node->geometry().width()/2), dest_node->geometry().y());
    QLineF line(sourcePoint, destPoint);


    // Draw the line
    painter->setPen(QPen(Qt::white, 1, Qt::DotLine, Qt::SquareCap, Qt::RoundJoin));
    painter->drawLine(line);
}
