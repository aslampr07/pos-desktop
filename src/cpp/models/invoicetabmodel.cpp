#include "invoicetabmodel.h"

InvoiceTabModel::InvoiceTabModel(QObject *parent): QAbstractListModel(parent)
{
    item.insert(0, true);
    for(int i = 1; i < 8; i++){
        item.insert(i, false);
    }
}

QVariant InvoiceTabModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(index)
    return QVariant(item[index.row()]);
}

int InvoiceTabModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 8;
}

void InvoiceTabModel::changeTab(int index)
{
    if(currentSelection != index){
        item[index] = true;
        QModelIndex newIndex = createIndex(index, 0);
        emit dataChanged(newIndex, newIndex);

        item[currentSelection] = false;
        QModelIndex oldIndex = createIndex(currentSelection, 0);
        emit dataChanged(oldIndex, oldIndex);
        currentSelection = index;
        emit tabChanged(index);
    }
}


