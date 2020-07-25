#ifndef ITEMTABLEMODEL_H
#define ITEMTABLEMODEL_H

#include<QAbstractTableModel>
#include<QString>
#include<QDateTime>
#include<QList>


class Item{

    QString m_name;
    QString m_code;
    QString m_alias;
    float m_price;
    QString m_createdat;

public:
    Item(const QString &name, const QString &code, const QString &alias, const float &price, const QString createdAt);

    QString name() const;
    QString code() const;
    QString alias() const;
    float price() const;
    QDateTime createdAt() const;
};

class ItemTableModel: public QAbstractTableModel
{
    Q_OBJECT

private:
    QList<Item> m_items;

public:
    ItemTableModel(QObject *parent = 0);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    void addItem(Item &item);


};

#endif // ITEMTABLEMODEL_H
