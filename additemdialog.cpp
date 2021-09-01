#include "additemdialog.h"
#include "ui_additemdialog.h"
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>


AddItemDialog::AddItemDialog(Item* &newItem, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddItemDialog)
{
    ui->setupUi(this);
    this->newItem = &newItem;
    imageFilePath = "none.png";

    // registers the events
    connect(ui->btnConfirmAdd, &QPushButton::clicked, this, &AddItemDialog::confirmAdd);

    connect(ui->btnLoadItemImg, &QPushButton::clicked, this, &AddItemDialog::loadItemImage);

    QDir pathDir("./images");
    if(!pathDir.exists())
    {
        // create it
        QDir().mkdir("./images");
    }
}

AddItemDialog::~AddItemDialog()
{
    delete ui;
}

void AddItemDialog::confirmAdd()
{
    QString productName = ui->labelProductName->text();
    int quantity = ui->spinQuantity->value();

    if(productName.trimmed() != "" && quantity >= 1)
    {
        *newItem = new Item(productName, quantity, imageFilePath);
        this->close();
    }
    else
    {
        QMessageBox mbox;
        mbox.setText("You must have a valid name and a quantity of at least 1");
        mbox.exec();
    }

}

void AddItemDialog::loadItemImage()
{
    QString filename;

    filename = QFileDialog::getOpenFileName(this, "Open Image", "./", "Image Files (*.png *.jpg");

    if(filename != "")
    {
        int lastSlash = filename.lastIndexOf("/");

        QString shortName = filename.right(filename.size() - lastSlash - 1);

        QFile::copy(filename, "./images/" + shortName);

        QPixmap pixmap("./images/" + shortName);

        ui->labelImage->setPixmap(pixmap);
        ui->labelImage->setScaledContents(true);

        imageFilePath = "./images/" + shortName;
    }
}
