#include "bt_connectionmodel.h"

ConnectionModel::ConnectionModel(QFrame *sourceNode, QFrame *destNode) : source(sourceNode), dest(destNode) {}

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
    QPoint sourcePoint(source->geometry().x()+(source->geometry().width()/2), source->geometry().y()+(source->geometry().height()));
    QPoint destPoint(dest->geometry().x()+(dest->geometry().width()/2), dest->geometry().y());
    QLineF line(sourcePoint, destPoint);


    // Draw the line
    painter->setPen(QPen(Qt::white, 1, Qt::DotLine, Qt::SquareCap, Qt::RoundJoin));
    painter->drawLine(line);
}
