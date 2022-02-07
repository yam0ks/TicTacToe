#include "x.h"

X::X(const QRectF &new_shape)
    :shape(new_shape)
{

}

QRectF X::boundingRect() const
{
    return shape;
}

void X::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    const int pen_width = 4;

    painter->setPen(QPen(Qt::red, pen_width, Qt::SolidLine));
    painter->drawLine(shape.x(), shape.y(), shape.x() + shape.width(), shape.y() + shape.height());
    painter->drawLine(shape.x() + shape.width(), shape.y(), shape.x(), shape.y() + shape.height());
}
