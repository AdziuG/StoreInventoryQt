#include "additemdialog.h"
#include "mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->menuNewProduct, &QAction::triggered, this, &MainWindow::handleMenuItemNew);
    connect(ui->btnRemoveProduct, &QPushButton::clicked, this, &MainWindow::removeItem);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// add item to productList(vector) and listProducts widget in mainwindow
void MainWindow::handleMenuItemNew()
{
    Item* newItem = nullptr;
    AddItemDialog addItemDialog(newItem, nullptr);

    addItemDialog.setModal(true);
    addItemDialog.exec();

    if(newItem != nullptr)
    {
        productList.push_back(newItem);
        ui->listProducts->addItem(newItem->getName());
    }
}

// remove item from list widget and productList(vector)
void MainWindow::removeItem()
{
    int index = this->ui->listProducts->currentRow();
    if(index != -1)
    {
        // remove from vector
        delete productList.at(index);
        productList.remove(index);

        // remove from list widget in the UI
        this->ui->listProducts->currentItem()->~QListWidgetItem();

    }
}

