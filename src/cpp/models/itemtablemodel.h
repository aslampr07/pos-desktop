#ifndef ITEMTABLEMODEL_H
#define ITEMTABLEMODEL_H

#include<QAbstractTableModel>
#include<QString>
#include<QDateTime>
#include<QList>


class ItemPod{

    QString m_name;
    QString m_code;
    QString m_alias;
    float m_price;
    QString m_createdat;

public:
    ItemPod(const QString &name, const QString &code, const QString &alias, const float &price, const QString createdAt);

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
    QList<ItemPod> m_items;

public:
    ItemTableModel(QObject *parent = 0);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    void addItem(ItemPod &item);

protected:
    QHash<int, QByteArray> roleNames() const override;
};

#endif // ITEMTABLEMODEL_H
