#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "interpolationsort.h"
#include "binpow.h"
#include <QTextEdit>
#include <QPushButton>
#include <ui_mainwindow.h>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    QTextEdit *textEdit;
    QPushButton *button;
    void processInput();
    InterpolationSort sorter;
    QVector<int> array;
    int mod;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
