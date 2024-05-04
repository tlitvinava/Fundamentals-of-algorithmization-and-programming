#include "mainwindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), textEdit(new QTextEdit), button(new QPushButton("Обработать"))
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(textEdit);
    layout->addWidget(button);
    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);

    connect(button, &QPushButton::clicked, this, &MainWindow::processInput);

    mod = 10007;
}

void MainWindow::processInput()
{
    QString inputText = textEdit->toPlainText();
    QStringList stringList = inputText.split(' ');

    QVector<int> array;
    for (const QString &str : stringList) {
        bool ok;
        int value = str.toInt(&ok);
        if (ok) {
            array.append(value);
        }
    }

    for(int i = 0; i < array.size(); i++) {
        //sorter.sort(array);
        sorter.sort(array, textEdit, i);

        QString sortedArray = "";
        for(int j = 0; j < array.size(); j++) {
            sortedArray += QString::number(array[j]) + " ";
        }
        //textEdit->append("Массив после шага " + QString::number(i+1) + ": " + sortedArray);
    }

    int index = sorter.getFoundIndex();
    int arrayLength = array.size();

    int result = BinPow::calculate(index, arrayLength, mod);
    textEdit->append("Результат: " + QString::number(result));
}

MainWindow::~MainWindow()
{
    delete textEdit;
    delete button;
}


void MainWindow::on_pushButton_clicked()
{
        int digit = ui->textEdit_2->text().toInt();
        int powder = arr.size() - 1;
        int mod = 1000000007;

        int result = binpow(digit, powder, mod);
        ui->output->append("Result of binpow: " + QString::number(result));
}

