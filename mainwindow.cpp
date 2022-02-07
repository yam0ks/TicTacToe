#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);
    ui->current_LSize_label->setText(QString::number(ui->LineSize_Slider->value()));
    ui->current_FSize_label->setText(QString::number(ui->FieldSize_Slider->value()));

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_DefaultGame_Button_clicked()
{
    const int square_params = 150;
    ui->stackedWidget->setCurrentIndex(2);
    setFixedSize(square_params * ui->FieldSize_Slider->value(), square_params * ui->FieldSize_Slider->value());

    rules.StartGame(ui->graphicsView);
}

void MainWindow::on_Settings_Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_SBack_Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_GBack_Button_clicked()
{
    const int window_params = 475;
    rules.FinishGame();
    setFixedSize(window_params, window_params);
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_LineSize_Slider_valueChanged(int value)
{
    ui->current_LSize_label->setText(QString::number(value));
    rules.SetLineSize(value);

    if(ui->FieldSize_Slider->value() < value){
        ui->current_FSize_label->setText(QString::number(value));
        ui->FieldSize_Slider->setValue(value);
        rules.SetSqrSize(value);
    }
}

void MainWindow::on_FieldSize_Slider_valueChanged(int value)
{
    ui->current_FSize_label->setText(QString::number(value));
    rules.SetSqrSize(value);

    if(ui->LineSize_Slider->value() > value){
        ui->current_LSize_label->setText(QString::number(value));
        ui->LineSize_Slider->setValue(value);
        rules.SetLineSize(value);
    }
}
