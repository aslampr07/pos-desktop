#include "invoicemodel.h"

InvoiceItem::InvoiceItem(const QString &code, const QString &name, const float &price, const int quantity)
    :m_code(code), m_name(name), m_price(price), m_quantity(quantity)
{

}

QString InvoiceItem::code() const
{
    return m_code;
}

QString InvoiceItem::name() const
{
    return m_name;
}

float InvoiceItem::price() const
{
    return m_price;
}

int InvoiceItem::quantity() const
{
    return m_quantity;
}

void InvoiceItem::setPrice(float price)
{
    m_price = price;
}

void InvoiceItem::setQuantity(int quantity)
{
    m_quantity = quantity;
}

/*************************************************************************************************/

InvoiceModel::InvoiceModel(QObject *parent): QAbstractListModel(parent)
{

}

void InvoiceModel::addInvoiceItem(const QString &code, const QString &name, const float &price)
{
    int index = -1;
    for(int i = 0; i < m_invoice.size(); i++){
        InvoiceItem &item = m_invoice[i];
        if(item.code() == code){
            index = i;
        }
    }
    if(index != -1){
        m_invoice[index].setQuantity(m_invoice[index].quantity() + 1);
        m_invoice[index].setPrice(m_invoice[index].quantity() * price);
        QModelIndex topLeft = createIndex(index,0);
        //To notify the item exists, and to update the UI
        emit dataChanged(topLeft, topLeft);
    }
    else {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_invoice << InvoiceItem(code, name, price, 1);
        endInsertRows();
    }
}

void InvoiceModel::removeInvoiceItem(const QString &code)
{
    int index = -1;
    for(int i = 0; i < m_invoice.size(); i++){
        InvoiceItem &item = m_invoice[i];
        if(item.code() == code){
            index = i;
        }
    }
    if(index != -1){
        int quantity = m_invoice[index].quantity();
        int price = m_invoice[index].price() / m_invoice[index].quantity();

        if(m_invoice[index].quantity() > 1){
             m_invoice[index].setQuantity(quantity - 1);
             m_invoice[index].setPrice(price * (quantity - 1));
             QModelIndex topLeft = createIndex(index,0);
             emit dataChanged(topLeft, topLeft);
        }
        else {
            beginRemoveRows(QModelIndex(), index, index);
            m_invoice.removeAt(index);
            endRemoveRows();
        }
    }
}

int InvoiceModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_invoice.size();
}

QVariant InvoiceModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= m_invoice.count())
        return QVariant();

    const InvoiceItem &invoice = m_invoice[index.row()];
    if(role == CodeRole){
        return invoice.code();
    }
    else if(role == NameRole){
        return invoice.name();
    }
    else if(role == PriceRole){
        return invoice.price();
    }
    else if(role == QuantityRole){
        return invoice.quantity();
    }

    return QVariant();
}

float InvoiceModel::total()
{
    float total = 0;
    for(int i = 0; i < m_invoice.size(); i++){
        total = total + m_invoice[i].price();
    }
    return total;
}

QJsonDocument InvoiceModel::invoiceJson()
{
    QJsonArray invoiceListArray;
    for(int i = 0; i < m_invoice.size(); i++){
        QJsonObject item
        {
            {"code", m_invoice[i].code()},
            {"quantity", m_invoice[i].quantity()}
        };
        invoiceListArray.insert(invoiceListArray.size(), item);
    }
    return QJsonDocument(invoiceListArray);
}

void InvoiceModel::clear()
{
    beginResetModel();
    m_invoice.clear();
    endResetModel();
}

void InvoiceModel::tabChanges(int index)
{
    qDebug()<<"Connected succesfully";
    qDebug()<<index;
}


QHash<int, QByteArray> InvoiceModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[CodeRole] = "code";
    roles[NameRole] = "name";
    roles[PriceRole] = "price";
    roles[QuantityRole] = "quantity";
    return roles;
}
