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
    for(int i = 0; i < 8; i++){
        m_tabbedinvoice << QVector<InvoiceItem>();
    }
}

void InvoiceModel::addInvoiceItem(const QString &code, const QString &name, const float &price)
{
    int index = -1;
    for(int i = 0; i < m_tabbedinvoice[currentPage].size(); i++){
        InvoiceItem &item = m_tabbedinvoice[currentPage][i];
        if(item.code() == code){
            index = i;
        }
    }
    if(index != -1){
        m_tabbedinvoice[currentPage][index].setQuantity(m_tabbedinvoice[currentPage][index].quantity() + 1);
        m_tabbedinvoice[currentPage][index].setPrice(m_tabbedinvoice[currentPage][index].quantity() * price);
        QModelIndex topLeft = createIndex(index,0);
        //To notify the item exists, and to update the UI
        emit dataChanged(topLeft, topLeft);
    }
    else {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_tabbedinvoice[currentPage] << InvoiceItem(code, name, price, 1);
        endInsertRows();
    }
}

void InvoiceModel::removeInvoiceItem(const QString &code)
{
    int index = -1;
    for(int i = 0; i < m_tabbedinvoice[currentPage].size(); i++){
        InvoiceItem &item = m_tabbedinvoice[currentPage][i];
        if(item.code() == code){
            index = i;
        }
    }
    if(index != -1){
        int quantity = m_tabbedinvoice[currentPage][index].quantity();
        int price = m_tabbedinvoice[currentPage][index].price() / m_tabbedinvoice[currentPage][index].quantity();

        if(m_tabbedinvoice[currentPage][index].quantity() > 1){
             m_tabbedinvoice[currentPage][index].setQuantity(quantity - 1);
             m_tabbedinvoice[currentPage][index].setPrice(price * (quantity - 1));
             QModelIndex topLeft = createIndex(index,0);
             emit dataChanged(topLeft, topLeft);
        }
        else {
            beginRemoveRows(QModelIndex(), index, index);
            m_tabbedinvoice[currentPage].removeAt(index);
            endRemoveRows();
        }
    }
}

int InvoiceModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_tabbedinvoice[currentPage].size();
}

QVariant InvoiceModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= m_tabbedinvoice[currentPage].count())
        return QVariant();

    const InvoiceItem &invoice = m_tabbedinvoice[currentPage][index.row()];
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
    for(int i = 0; i < m_tabbedinvoice[currentPage].size(); i++){
        total = total + m_tabbedinvoice[currentPage][i].price();
    }
    return total;
}

QJsonDocument InvoiceModel::invoiceJson()
{
    QJsonArray invoiceListArray;
    for(int i = 0; i < m_tabbedinvoice[currentPage].size(); i++){
        QJsonObject item
        {
            {"code", m_tabbedinvoice[currentPage][i].code()},
            {"quantity", m_tabbedinvoice[currentPage][i].quantity()}
        };
        invoiceListArray.insert(invoiceListArray.size(), item);
    }
    return QJsonDocument(invoiceListArray);
}

void InvoiceModel::clear()
{
    beginResetModel();
    m_tabbedinvoice[currentPage].clear();
    endResetModel();
}

void InvoiceModel::tabChanges(int index)
{
    beginResetModel();
    currentPage = index;
    endResetModel();
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
