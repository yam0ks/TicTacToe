#ifndef TABLE_H
#define TABLE_H
#pragma once

#include <QGraphicsObject>
#include <QRectF>
#include <QPainter>
#include <QGraphicsScene>
#include <QVector>
#include <QGraphicsSceneMouseEvent>

#include "x.h"
#include "o.h"

enum value_type{
 X,
 O,
 T,
 N
};

namespace Table_ {
class Square : public QGraphicsObject
{
    Q_OBJECT

  public:
    explicit Square(const QRectF& new_shape);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    QRectF GetShape() const;

    void SetValue(QGraphicsItem* item);
    QGraphicsItem* GetValue();

    void SetType(const value_type new_type);
    value_type GetType() const;

    void Clear(QGraphicsScene* scene);

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    ~Square();

  private:
    QRectF shape;
    QGraphicsItem* value = nullptr;
    value_type type_;

  signals:
    void NewTurn(Square* square);
    void TurnMade(Square* square);
};
}

class Table : public QObject
{
  Q_OBJECT

public:

    Table();
    void DrowTable(const int sqr_size);
    void DrowSquare(const int xCoordinate, const int yCoordinate, const int sqr_size);
    bool PaintValue(Table_::Square* square, const value_type current_type);
    void ClearSquares();
    void ClearField();
    void SetTurn(value_type current_turn);

    QGraphicsScene* GetScene();
    QVector<Table_::Square*>& GetSquares();

    ~Table();

private:
    QVector<Table_::Square*> squares;
    QGraphicsScene* scene;
    value_type turn = value_type::X;

signals:
    void TurnMade(Table_::Square* square);

private slots:
    void NewTurn(Table_::Square* square);
};



#endif // TABLE_H
