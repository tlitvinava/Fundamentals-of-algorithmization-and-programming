#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <INCLUDES.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_parsing_clicked()
{
    // Очистка всех списков
    QList<QListWidget*> listWidgets = { ui->listWidget, ui->listWidget_2, ui->listWidget_3, ui->listWidget_4, ui->listWidget_5, ui->listWidget_6 };
    for(auto listWidget : listWidgets){
        listWidget->clear();
    }

    auto str = ui->input_code->toPlainText().toStdString();

    Parser pars(std::move(str));


    // Заполнение списка ui->listWidget данными о переменных
    for(auto v : pars.getVariables()){
        QString itemText = "Variables: " + QString::fromStdString(v.getType() + " " + v.getName() + " = " +
                                                                  v.getDefaultvalue() + " " + v.getVisibilityArea() + "\n" + v.getPositions());
        ui->listWidget->addItem(itemText);
    }

    // Заполнение списка ui->listWidget_2 данными о функциях
    for(auto v : pars.getFunctions()){
        QString itemText = "Prototypes: " + QString::fromStdString(v.getPrototype() + "\nOverload: " + v.getOverloadsFunctions());
        ui->listWidget_2->addItem(itemText);
    }

    // Заполнение списка ui->listWidget_3 данными об изменении переменных
    for(auto v : pars.getChangePosition()){
        QString itemText = "Change of variables:\nColumn: " + QString::number(v.first) + ", Line: " + QString::number(v.second) + "\n";
        ui->listWidget_3->addItem(itemText);
    }

    // Заполнение списка ui->listWidget_4 данными о ветвлениях
    for(auto v : pars.getBranches()){
        QString itemText = "Branch line: " + QString::number(v.first) + ", branching depth: " + QString::number(v.second) + "\n";
        ui->listWidget_4->addItem(itemText);
    }

    // Заполнение списка ui->listWidget_5 данными о сложных структурах
    ui->listWidget_5->addItem("Number of classes : " + QString::number(pars.getComplexStructs()[0]) + "\n" +
                              "Number of structures : " + QString::number(pars.getComplexStructs()[1]) + "\n" +
                              "Number of dynamic arrays : " + QString::number(pars.getComplexStructs()[2]) + "\n" +
                              "Number of static arrays : " + QString::number(pars.getComplexStructs()[3]) + "\n");
    pair<int, int> errors = pars.searchInfiniteLoops();
    if (errors.first == -1 && errors.second == -1) {
        ui->listWidget_6->addItem("no infinite loops found.");
    } else {
        QString itemText = "Infinite loop on a line " + QString::number(errors.first) + ", branching depth: " + QString::number(errors.second) + "\n";
        ui->listWidget_6->addItem(itemText);

    }
}

void MainWindow::on_open_file_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Open a file", "D:", tr("source files (*.cpp *.h)"));

    QFile file(file_name);
    if (file.size() == 0) {
        QMessageBox::information(this, "Title", "Вы открыли пустой файл");
    } else if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream in(&file);
        QString text = in.readAll();
        ui->input_code->setPlainText(text);
        file.close();
    } else {
        QMessageBox::critical(this, "Error", "Не удалось открыть файл");
    }
}
