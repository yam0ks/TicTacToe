#include "o.h"

O::O(const QRectF &new_shape)
    :shape(new_shape)
{}

QRectF O::boundingRect() const
{
    return shape;
}

void O::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    const int pen_width = 4;

    painter->setPen(QPen(Qt::red, pen_width, Qt::SolidLine));
    painter->drawEllipse(shape);
}
