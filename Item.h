#ifndef ITEM_H
#define ITEM_H
#include <QString>


class Item
{
    public:
        Item(QString name, int quantity, QString imageFilePath="none.png");
        void setName(QString inputName);
        QString getName() const;
        void setQuantity(int inputQuantity);
        int getQuantity() const;
        void setImageFilePath(QString insertImageFilePath);
        const QString getImageFilePath() const;

private:
        QString name;
        int quantity;
        QString imageFilePath;

};
#endif // ITEM_H
