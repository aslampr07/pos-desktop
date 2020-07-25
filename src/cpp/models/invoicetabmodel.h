#ifndef INVOICETABMODEL_H
#define INVOICETABMODEL_H

#include <QObject>
#include <QAbstractListModel>

class InvoiceTabModel: public QAbstractListModel
{
    Q_OBJECT

private:
    QList<bool> item;
    int currentSelection = 0;

public:
    InvoiceTabModel(QObject *parent = 0);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    void changeTab(int index);

signals:
    void tabChanged(int index);

};

#endif // INVOICETABMODEL_H
