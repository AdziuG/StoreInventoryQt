#include "additemdialog.h"
#include "mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "updateitemdialog.h"
#include <QDir>
#include <QFile>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->menuNewProduct, &QAction::triggered, this, &MainWindow::handleMenuItemNew);
    connect(ui->btnRemoveProduct, &QPushButton::clicked, this, &MainWindow::removeItem);
    connect(ui->listProducts, &QListWidget::itemClicked, this, &MainWindow::handleItemClick);
    connect(ui->menuEditSelectedProduct, &QAction::triggered, this, &MainWindow::handleMenuItemEdit);
    connect(ui->menuSaveProducts, &QAction::triggered, this, &MainWindow::handleSaveItems);
    connect(ui->menuLoadProducts, &QAction::triggered, this, &MainWindow::handleLoadItems);
}

MainWindow::~MainWindow()
{
    // free ip product list memory
    for(Item* product : productList)
    {
        delete product;
    }
    productList.clear();
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

void MainWindow::handleSaveItems()
{
    QFile outputFile("products.txt");

    outputFile.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream out(&outputFile);

    for(Item* product: productList)
    {
        out<<product->getName()<<",";
        out<<product->getQuantity()<<",";
        out<<product->getImageFilePath()<<Qt::endl;
    }

    out.flush();
    outputFile.close();

}

void MainWindow::handleLoadItems()
{
    QFile inputFile("products.txt");
    inputFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&inputFile);

    // clear current list and vector
    for(Item* temp: productList)
    {
        delete temp;
    }

    productList.clear();    // data model
    ui->listProducts->clear();  //view/ui

    while(!in.atEnd())
    {
        QString line = in.readLine();
        QStringList info = line.split(",");

        // handle list of products in UI
        ui->listProducts->addItem(info.at(0));

        // handle vector
        Item* product = new Item(info.at(0), info.at(1).toInt(), info.at(2));

        productList.push_back(product);
    }

    in.flush();
    inputFile.close();
}
