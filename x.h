#ifndef X_H
#define X_H
#pragma once

#include <QGraphicsItem>
#include <QPainter>

class X : public QGraphicsItem
{
public:
    explicit X(const QRectF& new_shape);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QRectF shape;
};

#endif // X_H
