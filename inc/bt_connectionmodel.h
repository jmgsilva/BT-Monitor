#ifndef BT_CONNECTIONMODEL_H
#define BT_CONNECTIONMODEL_H

#include <QPainter>
#include <QGraphicsItem>
#include <QFrame>

class ConnectionModel : public QGraphicsItem {
    QFrame *source, *dest;

public:
    ConnectionModel(QFrame *source, QFrame *dest);

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // BT_CONNECTIONMODEL_H
