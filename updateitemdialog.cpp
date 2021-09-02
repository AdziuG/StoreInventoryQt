#include "updateitemdialog.h"
#include "ui_updateitemdialog.h"
#include <QFileDialog>
#include <QMessageBox>

UpdateItemDialog::UpdateItemDialog(Item* currentItem, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateItemDialog)
{
    ui->setupUi(this);
    this->currentItem = currentItem;

    if(currentItem != nullptr)
    {
        ui->labelItemName->setText(currentItem->getName());
        QPixmap pixmap(currentItem->getImageFilePath());
        ui->itemImage->setPixmap(pixmap);

        ui->spinQuantity->setValue(currentItem->getQuantity());
        imageFilePath = currentItem->getImageFilePath();
    }

    // connections
    connect(ui->btnConfirmEdit, &QPushButton::clicked, this, &UpdateItemDialog::confirmUpdate);
    connect(ui->btnItemImage, &QPushButton::clicked, this, &UpdateItemDialog::loadItemImage);
}

UpdateItemDialog::~UpdateItemDialog()
{
    delete ui;
}

void UpdateItemDialog::confirmUpdate()
{
    int quantity = ui->spinQuantity->value();

    if(quantity >= 1)
    {
        currentItem->setQuantity(quantity);
        currentItem->setImageFilePath(imageFilePath);
        this->close();
    }
    else
    {
        QMessageBox mbox;
        mbox.setText("Quantity must be at least 1");
        mbox.exec();
    }
}

void UpdateItemDialog::loadItemImage()
{
    QString filename;
    filename = QFileDialog::getOpenFileName(this, "Open Image", "./", "Image Files (*.png *.jpg)");

    if(filename != "")
    {
        int lastSlash = filename.lastIndexOf("/");

        QString shortName = filename.right(filename.size() - lastSlash - 1);

        QFile::copy(filename, "./images/" + shortName);

        QPixmap pixmap("./images/" + shortName);

        ui->itemImage->setPixmap(pixmap);
        ui->itemImage->setScaledContents(true);

        imageFilePath = "./images/" + shortName;
    }
}
