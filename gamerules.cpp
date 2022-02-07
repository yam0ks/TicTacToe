#include "gamerules.h"

GameRules::GameRules()
    : table(new Table())
{
}

value_type GameRules::SearchWinner(const QVector<Table_::Square*>& squares, const int index) const
{
    value_type current_check;

    current_check = CheckRow(squares, index);
    if(current_check != value_type::N)
        return current_check;

    current_check =  CheckColumn(squares, index);
    if(current_check != value_type::N)
        return current_check;

    current_check =  CheckMainDiagonal(squares, index);
    if(current_check != value_type::N)
        return current_check;

    current_check =  CheckSideDiagonal(squares, index);
    if(current_check != value_type::N)
        return current_check;

    return CheckForTie(squares);
}

value_type GameRules::CheckRow(const QVector<Table_::Square*>& squares, const int index) const
{
    int col_numb = index % sqr_size;

    QVector<Table_::Square*> temp;

    for(int i = index - qMin(line_size - 1, col_numb); i < index; i++){   //Цикл от начала строки до индекса
        if((line_size - 1) > (sqr_size - i % sqr_size - 1))               //Если длина выигрышной строки больше оставшейся длины строки, лив
            break;
        for(int j = 0; j < line_size; j++)                                //Закладываем серию в вектор
            temp.push_back(squares[i + j]);
        value_type current = CheckLine(temp);                             //Проверяем на победу
        if(current != value_type::N) return current;
        temp.clear();
    }

    if( (line_size - 1) <= (sqr_size - col_numb - 1) ){                   //Если после индекса хватает места, чтобы набрать выигрышную комбинацию, проверяем
        for(int j = 0; j < line_size; j++)
            temp.push_back(squares[index + j]);
        value_type current = CheckLine(temp);
        if(current != value_type::N) return current;
        temp.clear();
    }

    return value_type::N;
}

value_type GameRules::CheckColumn(const QVector<Table_::Square*> &squares, const int index) const
{
    QVector<Table_::Square*> temp;
    int row_numb = index / sqr_size;

    for(int i = index - qMin(line_size - 1, row_numb) * sqr_size; i < index ; i += sqr_size){
        if((line_size - 1) > (sqr_size - i / sqr_size - 1))
            break;
        temp.push_back(squares[i]);
        for(int j = 1; j < line_size; j++)
            temp.push_back(squares[i + j * sqr_size]);
        value_type current = CheckLine(temp);
        if(current != value_type::N) return current;
        temp.clear();
    }

    if( (line_size - 1) <= (sqr_size - row_numb - 1) ){
        temp.push_back(squares[index]);
        for(int j = 1; j < line_size; j++)
            temp.push_back(squares[index + j * sqr_size]);
        value_type current = CheckLine(temp);
        if(current != value_type::N) return current;
        temp.clear();
    }

    return value_type::N;
}

value_type GameRules::CheckMainDiagonal(const QVector<Table_::Square*> &squares, const int index) const
{
    int row_numb = index / sqr_size;
    int col_numb = index % sqr_size;
    QVector<Table_::Square*> temp;

    int lt_border = index - (sqr_size + 1) * qMin(row_numb, col_numb);
    int rb_border = index + (sqr_size + 1) * qMin((sqr_size - row_numb - 1), (sqr_size - col_numb - 1));

    for(int i = index - qMin(line_size - 1, (index - lt_border) / (sqr_size + 1) ) * (sqr_size + 1); i < index; i += (sqr_size + 1) ){
        if((line_size - 1) > (rb_border - i) / (sqr_size + 1))
            break;
        temp.push_back(squares[i]);
        for(int j = 1; j < line_size; j++)
            temp.push_back(squares[i + j * (sqr_size + 1)]);
        value_type current = CheckLine(temp);
        if(current != value_type::N) return current;
        temp.clear();
    }

    if( (line_size - 1) <= (rb_border - index) / (sqr_size + 1) ){
        temp.push_back(squares[index]);
        for(int j = 1; j < line_size; j++)
            temp.push_back(squares[index + j * (sqr_size + 1)]);
        value_type current = CheckLine(temp);
        if(current != value_type::N) return current;
        temp.clear();
    }

    return value_type::N;
}

value_type GameRules::CheckSideDiagonal(const QVector<Table_::Square*> &squares, const int index) const
{
    int row_numb = index / sqr_size;
    int col_numb = index % sqr_size;
    QVector<Table_::Square*> temp;

    int rt_border = index - (sqr_size - 1) * qMin(row_numb, (sqr_size - col_numb - 1));
    int lb_border = index + (sqr_size - 1) * qMin((sqr_size - row_numb - 1), col_numb);

    for(int i = index - qMin(line_size - 1, (index - rt_border) / (sqr_size - 1) ) * (sqr_size - 1); i < index; i += (sqr_size - 1) ){
        if((line_size - 1) > (lb_border - i) / (sqr_size - 1))
            break;
        temp.push_back(squares[i]);
        for(int j = 1; j < line_size; j++)
            temp.push_back(squares[i + j * (sqr_size - 1)]);
        value_type current = CheckLine(temp);
        if(current != value_type::N) return current;
        temp.clear();
    }

    if( (line_size - 1) <= (lb_border - index) / (sqr_size - 1) ){
        temp.push_back(squares[index]);
        for(int j = 1; j < line_size; j++)
            temp.push_back(squares[index + j * (sqr_size - 1)]);
        value_type current = CheckLine(temp);
        if(current != value_type::N) return current;
        temp.clear();
    }

    return value_type::N;
}

value_type GameRules::CheckLine(const QVector<Table_::Square*> &squares) const
{
    value_type current_type = squares[0]->GetType();
    for(const auto& square : squares){
        if(square->GetType() != current_type || current_type == value_type::N)
            return value_type::N;
    }
    return current_type;
}

value_type GameRules::CheckForTie(const QVector<Table_::Square*> &squares) const
{
    bool tied = true;

    for(const auto& square : squares){
        if(square->GetType() == value_type::N)
            tied = false;
    }

    return (tied) ? value_type::T : value_type::N;
}

void GameRules::SetLineSize(const int new_size)
{
    line_size = new_size;
}

int GameRules::GetLineSize()
{
    return line_size;
}

void GameRules::SetSqrSize(const int new_size)
{
    sqr_size = new_size;
}

int GameRules::GetSqrSize()
{
    return sqr_size;
}

void GameRules::StartGame(QGraphicsView *view)
{
    const int offset = 2;

    view->setScene(table->GetScene());
    table->GetScene()->setSceneRect(0, 0, view->width() - offset, view->height() - offset);

    table->DrowTable(sqr_size);
    table->GetScene()->setBackgroundBrush(QBrush(Qt::gray));

    connect(table, &Table::TurnMade, this, &GameRules::AfterTurnMade);
}

void GameRules::FinishGame()
{
    table->ClearField();
    table->SetTurn(value_type::X);
}

GameRules::~GameRules()
{
    delete table;
}

void GameRules::AfterTurnMade(Table_::Square *square)
{
    auto it = std::find(table->GetSquares().begin(), table->GetSquares().end(), square);
    int index = it - table->GetSquares().begin();

    switch(SearchWinner(table->GetSquares(), index)){
        case value_type::X :
            QMessageBox::warning(nullptr, "", "X wins!");
            table->ClearSquares();
            table->SetTurn(value_type::X);
        break;
        case value_type::O :
            QMessageBox::warning(nullptr, "", "O wins!");
            table->ClearSquares();
            table->SetTurn(value_type::X);
        break;
        case value_type::T :
            QMessageBox::warning(nullptr, "", "You tied!");
            table->ClearSquares();
            table->SetTurn(value_type::X);
        break;
        default : break;
    }
}
