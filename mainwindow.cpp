#include "additemdialog.h"
#include "mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "updateitemdialog.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->menuNewProduct, &QAction::triggered, this, &MainWindow::handleMenuItemNew);
    connect(ui->btnRemoveProduct, &QPushButton::clicked, this, &MainWindow::removeItem);
    connect(ui->listProducts, &QListWidget::itemClicked, this, &MainWindow::handleItemClick);
    connect(ui->menuEditSelectedProduct, &QAction::triggered, this, &MainWindow::handleMenuItemEdit);
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

void MainWindow::handleItemClick()
{
    int index = ui->listProducts->currentRow();
    if(index != -1)
    {
        Item* currentItem = productList.at(index);

        if(currentItem != nullptr)
        {
            ui->labelProductName->setText(currentItem->getName());
            ui->labelQuantity->setText(QString::number(currentItem->getQuantity()));
            QPixmap pixmap(currentItem->getImageFilePath());
            ui->labelItemImage->setPixmap(pixmap);
            ui->labelItemImage->setScaledContents(true);
        }

    }

}

void MainWindow::handleMenuItemEdit()
{
    int index = ui->listProducts->currentRow();
    if(index != -1)
    {
        Item* currentItem = productList.at(index);

        if(currentItem != nullptr)
        {
            UpdateItemDialog updateItemDialog(currentItem, nullptr);
            updateItemDialog.exec();

            // make sure UI is updated
            ui->labelProductName->setText(currentItem->getName());
            ui->labelQuantity->setText(QString::number(currentItem->getQuantity()));
            QPixmap pixmap(currentItem->getImageFilePath());
            ui->labelItemImage->setPixmap(pixmap);
            ui->labelItemImage->setScaledContents(true);

        }
    }

}
