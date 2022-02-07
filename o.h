#ifndef O_H
#define O_H
#pragma once

#include <QGraphicsItem>
#include <QPainter>
class O : public QGraphicsItem
{
public:
    explicit O(const QRectF& new_shape);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QRectF shape;
};

#endif // O_H
