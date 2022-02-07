#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once

#include <QMainWindow>

#include "gamerules.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GameRules rules;

private slots:
    void on_DefaultGame_Button_clicked();
    void on_Settings_Button_clicked();
    void on_SBack_Button_clicked();
    void on_GBack_Button_clicked();
    void on_LineSize_Slider_valueChanged(int value);
    void on_FieldSize_Slider_valueChanged(int value);
};
#endif // MAINWINDOW_H
