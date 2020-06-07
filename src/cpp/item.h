#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <QAbstractListModel>
#include <QSortFilterProxyModel>

#include "service.h"
#include "models/itemtablemodel.h"

class Product : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int slNumber MEMBER m_slNumber)
    Q_PROPERTY(QString code MEMBER m_code)
    Q_PROPERTY(QString itemName MEMBER m_name)
    Q_PROPERTY(QString itemAlias MEMBER m_alias)
    Q_PROPERTY(float price MEMBER m_price)
    Q_PROPERTY(QString createdAt MEMBER m_createdAt)

public:
    Product(QObject *parent = nullptr);
    Product(int slNumber, QString &code, QString &name, QString &alias, double &price, QString &createdAt, QObject *parent = nullptr);

private:
    int m_slNumber;
    QString m_code;
    QString m_name;
    QString m_alias;
    float m_price;
    QString m_createdAt;

};

class ItemComponent : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ItemTableModel* model READ itemModel CONSTANT)
    Q_PROPERTY(QSortFilterProxyModel* filterModel READ filterModell CONSTANT)
    Service service;
    void networkError();
    ItemTableModel* m_model;
    ItemTableModel* itemModel() const;
    QSortFilterProxyModel* m_filter_model;
    QSortFilterProxyModel* filterModell() const;

public:
    explicit ItemComponent(QObject *parent = nullptr);
    ~ItemComponent();

public slots:
    void createItem(QString name, QString alias, float price, bool isSaveNew);
    void loadItemList();
    void filterItems(QString filter);

signals:
    void itemInsertSuccess(bool isSaveNew);
    void itemListFetched(QList<Product*> product);
    void nameInputError(QString error);
    void aliasInputError(QString error);
    void priceInputError(QString error);
};



#endif // ITEM_H








