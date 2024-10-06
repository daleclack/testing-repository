#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create a simple list model
    QStringList list;
    list.append("test1");
    list.append("test2");
    list.append("test3");

    QStringListModel *listmodel = new QStringListModel(list);

    ui->listView->setModel(listmodel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_add_clicked()
{
    QString str_item = ui->line_item->text();

    // Return when the item is empty
    if (str_item.isEmpty()){
        return;
    }

    // Use insert to add item
    QStringList list = listmodel->stringList();
    list.append(str_item);
    listmodel->setStringList(list);
}

