#ifndef ITEM_H
#define ITEM_H

#include <QObject>

#include "service.h"

class Item : public QObject
{
    Q_OBJECT

    Service service;
    void networkError();
public:
    explicit Item(QObject *parent = nullptr);

public slots:
    void createItem(QString name, QString alias, float price, bool isSaveNew);

signals:
    void success(bool isSaveNew);
    void nameInputError(QString error);
    void aliasInputError(QString error);
    void priceInputError(QString error);
};

#endif // ITEM_H
