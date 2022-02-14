#include "table.h"

Table::Table()
    :scene(new QGraphicsScene())
{
}

void Table::DrowTable(const int sqr_size)
{
    squares.reserve(sqr_size * sqr_size);

    qreal xCoordinate = 0.35 * sqr_size;
    qreal yCoordinate = 0;

    Table_::Square* square = new Table_::Square(QRect(xCoordinate, yCoordinate, scene->width() / qreal(sqr_size), scene->height() / qreal(sqr_size)));
    scene->addItem(square);
    squares.push_back(square);

    connect(square, &Table_::Square::NewTurn, this, &Table::NewTurn);
    connect(square, &Table_::Square::TurnMade, this, &Table::TurnMade);

    DrowSquare(scene->width() / qreal(sqr_size) + xCoordinate, yCoordinate, sqr_size);
}

void Table::DrowSquare(const qreal xCoordinate,const qreal yCoordinate,const int sqr_size)
{
    const qreal offset = 0.35 * sqr_size;
    if(xCoordinate >= scene->width() - offset && yCoordinate + scene->height() / qreal(sqr_size) >= scene->height() - offset)
        return;

    if(xCoordinate >= scene->width() - offset){
        DrowSquare(offset, yCoordinate + scene->height() / sqr_size, sqr_size);
        return;
    }

    Table_::Square* square = new Table_::Square(QRect(xCoordinate, yCoordinate, scene->width() / qreal(sqr_size), scene->height() / qreal(sqr_size)));
    scene->addItem(square);
    squares.push_back(square);

    connect(square, &Table_::Square::NewTurn, this, &Table::NewTurn);
    connect(square, &Table_::Square::TurnMade, this, &Table::TurnMade);

    DrowSquare(xCoordinate + scene->width() / qreal(sqr_size), yCoordinate, sqr_size);
}

bool Table::PaintValue(Table_::Square* square, const value_type current_turn)
{
    if(square->GetValue() != nullptr)
        return false;

    switch(current_turn){
        case value_type::X :
            square->SetValue(new class X(square->GetShape()));
            scene->addItem(square->GetValue());
            square->SetType(value_type::X);
        break;
        case value_type::O :
            square->SetValue(new class O(square->GetShape()));
            scene->addItem(square->GetValue());
            square->SetType(value_type::O);
        break;
        default: break;
    }
    return true;
}

void Table::ClearSquares()
{
    for(auto& square: squares){
        square->Clear(scene);
    }
}

void Table::ClearField()
{
    scene->clear();
    squares.clear();
}

void Table::SetTurn(value_type current_turn)
{
    turn = current_turn;
}

QGraphicsScene *Table::GetScene()
{
    return scene;
}

QVector<Table_::Square *> &Table::GetSquares()
{
    return squares;
}

void Table::NewTurn(Table_::Square *square)
{
    if(PaintValue(square, turn)){
        square->SetType(turn);
        turn = (turn == value_type::X) ? value_type::O : value_type::X;
    }
}

Table::~Table()
{
    for(auto& square : squares){
        delete square;
    }
    delete scene;
}

Table_::Square::Square(const QRectF &new_shape)
    : shape(new_shape), type_(value_type::N)
{

}

QRectF Table_::Square::boundingRect() const
{
    return shape;
}

void Table_::Square::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    const int pen_width = 5;

    painter->setPen(QPen(Qt::black, pen_width, Qt::SolidLine));
    painter->drawRect(shape);
}

QRectF Table_::Square::GetShape() const
{
    return shape;
}

void Table_::Square::SetValue(QGraphicsItem *item)
{
    value = item;
}

QGraphicsItem *Table_::Square::GetValue() const
{
    return value;
}

void Table_::Square::SetType(const value_type new_type)
{
    type_ = new_type;
}

value_type Table_::Square::GetType() const
{
    return type_;
}

void Table_::Square::Clear(QGraphicsScene *scene)
{
    if(value == nullptr)
        return;

    scene->removeItem(value);
    delete value;
    value = nullptr;
    type_ = value_type::N;
}

void Table_::Square::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    emit(NewTurn(this));
}

void Table_::Square::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    emit(TurnMade(this));
}

Table_::Square::~Square()
{
    delete value;
}
