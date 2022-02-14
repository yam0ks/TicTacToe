#ifndef GAMERULES_H
#define GAMERULES_H
#pragma once

#include <QtMath>
#include <QMessageBox>
#include <QGraphicsView>

#include "table.h"

constexpr static int default_size = 3;

class GameRules : public QObject
{
    Q_OBJECT

public:
    GameRules() = default;
    value_type SearchWinner(const QVector<Table_::Square*>& squares, const int index) const;

    void SetLineSize( const int new_size);
    qreal GetLineSize() const;

    void SetSqrSize(const int new_size);
    qreal GetSqrSize() const;

    void StartGame(QGraphicsView* view);
    void FinishGame();

private:
    value_type CheckRow(const QVector<Table_::Square*>& squares, const int index) const;
    value_type CheckColumn(const QVector<Table_::Square*>& squares, const int index) const;
    value_type CheckMainDiagonal(const QVector<Table_::Square*>& squares, const int index) const;
    value_type CheckSideDiagonal(const QVector<Table_::Square*>& squares, const int index) const;
    value_type CheckLine(const QVector<Table_::Square*>& squares) const;
    value_type CheckForTie(const QVector<Table_::Square*>& squares) const;

    int line_size = default_size;
    int sqr_size = default_size;
    Table table;
    bool changed = true;

private slots:
    void AfterTurnMade(Table_::Square* square);
};

#endif // GAMERULES_H
