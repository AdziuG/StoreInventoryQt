#include "Item.h"


Item::Item(QString name, int quantity, QString imageFilePath)
{
    setName(name);
    setQuantity(quantity);
    imageFilePath = "none.png";
}

void Item::setName(QString inputName)
{
    this->name = inputName;
}

QString Item::getName() const
{
    return name;
}

void Item::setQuantity(int inputQuantity)
{
    this->quantity = inputQuantity;
}

int Item::getQuantity() const
{
    return quantity;
}

void Item::setImageFilePath(QString insertImageFilePath="none.png")
{
    this->imageFilePath = insertImageFilePath;
}

const QString Item::getImageFilePath() const
{
    return imageFilePath;
}
