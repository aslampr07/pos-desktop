#ifndef INVOICE_H
#define INVOICE_H

#include <QObject>
#include <QString>

#include "service.h"
#include "models/invoicetabmodel.h"
#include "models/invoicemodel.h"


class Invoice : public QObject
{
    Q_OBJECT
    Q_PROPERTY(InvoiceModel* model READ invoiceModel CONSTANT)
    Q_PROPERTY(InvoiceTabModel* tabmodel READ invoiceTabModel CONSTANT)
private:
    InvoiceModel* m_model;
    InvoiceModel* invoiceModel() const;
    InvoiceTabModel* m_tabmodel;
    InvoiceTabModel *invoiceTabModel() const;
    Service service;
    bool saveButtonLock = false;
public:
    explicit Invoice(QObject *parent = nullptr);
    ~Invoice();

public slots:
    void addItemToInvoice(QString code, QString name, float price);
    void removeItemFromInvoice(QString code);
    void createInvoice();
    void tabItemClicked(int index);


signals:
    void invoiceItemChange(float total);
    void invoiceTabChanged(QList<bool> list);
};

#endif // INVOICE_H
