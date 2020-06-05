#include "itemtablemodel.h"

#include <QDebug>

ItemPod::ItemPod(const QString &name, const QString &code, const QString &alias, const float &price, const QString createdAt):
    m_name(name), m_code(code), m_alias(alias), m_price(price), m_createdat(createdAt)
{

}

QString ItemPod::name() const
{
    return m_name;
}

QString ItemPod::code() const
{
    return m_code;
}

QString ItemPod::alias() const
{
    return m_alias;
}

float ItemPod::price() const
{
    return m_price;
}

QDateTime ItemPod::createdAt() const
{
    return QDateTime::fromString(m_createdat,Qt::DateFormat::ISODateWithMs);
}


ItemTableModel::ItemTableModel(QObject *parent) : QAbstractTableModel(parent)
{

}

QVariant ItemTableModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole){
        switch (index.column()) {
            case 0:
                return QVariant(index.row() + 1);
            case 1:
                return QVariant(m_items[index.row()].alias());
            case 2:
                return QVariant(m_items[index.row()].name());
            case 3:
                return QVariant(QString("₹ %1").arg(m_items[index.row()].price()));
            case 4:
                return QVariant(m_items[index.row()].createdAt().toString("dd-MMMM-yyyy"));
            case 5:
                return QVariant(m_items[index.row()].code());
            default:
                return QVariant();
        }
    }
    else{
        return QVariant();
    }
}

int ItemTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_items.size();
}

int ItemTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 6;
}

void ItemTableModel::addItem(ItemPod &item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_items << item;
    endInsertRows();
}

QHash<int, QByteArray> ItemTableModel::roleNames() const
{
    return { {Qt::DisplayRole, "display"} };
}

