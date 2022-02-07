#ifndef GAMERULES_H
#define GAMERULES_H
#pragma once

#include <QtMath>
#include <QMessageBox>
#include <QGraphicsView>

#include "table.h"

class GameRules : public QObject
{
    Q_OBJECT

public:
    GameRules();
    value_type SearchWinner(const QVector<Table_::Square*>& squares, const int index) const;
    value_type CheckRow(const QVector<Table_::Square*>& squares, const int index) const;
    value_type CheckColumn(const QVector<Table_::Square*>& squares, const int index) const;
    value_type CheckMainDiagonal(const QVector<Table_::Square*>& squares, const int index) const;
    value_type CheckSideDiagonal(const QVector<Table_::Square*>& squares, const int index) const;
    value_type CheckLine(const QVector<Table_::Square*>& squares) const;
    value_type CheckForTie(const QVector<Table_::Square*>& squares) const;

    void SetLineSize( const int new_size);
    int GetLineSize();

    void SetSqrSize(const int new_size);
    int GetSqrSize();

    void StartGame(QGraphicsView* view);
    void FinishGame();

    ~GameRules();
private:
    int line_size = 3;
    int sqr_size = 3;
    Table* table;
    bool changed = true;

private slots:
    void AfterTurnMade(Table_::Square* square);
};

#endif // GAMERULES_H
