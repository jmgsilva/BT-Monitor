#include "connectionmodel.h"

ConnectionModel::ConnectionModel(NodeModel *sourceNode, NodeModel *destNode) : source(sourceNode), dest(destNode)
{
    dest->setParent(source);
    dest->setConnection(this);
}

QRectF ConnectionModel::boundingRect() const
{
    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize = 10;

    if (!source || !dest)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth + arrowSize) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

void ConnectionModel::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPoint sourcePoint(source->getNodeFrame()->geometry().x()+(source->getNodeFrame()->geometry().width()/2), source->getNodeFrame()->geometry().y()+(source->getNodeFrame()->geometry().height()));
    QPoint destPoint(dest->getNodeFrame()->geometry().x()+(dest->getNodeFrame()->geometry().width()/2), dest->getNodeFrame()->geometry().y());
    QLineF line(sourcePoint, destPoint);


    // Draw the line
    painter->setPen(QPen(Qt::white, 1, Qt::DotLine, Qt::SquareCap, Qt::RoundJoin));
    painter->drawLine(line);
}
