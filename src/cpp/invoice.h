#ifndef INVOICE_H
#define INVOICE_H

#include <QObject>
#include <QString>
#include <QAbstractListModel>
#include <QHash>
#include <QJsonDocument>

#include "service.h"

class InvoiceItem{
public:
    InvoiceItem(const QString& code, const QString& name, const float& price, const int quantity);

    QString code() const;
    QString name() const;
    float price() const;
    int quantity() const;

    void setPrice(float price);
    void setQuantity(int quantity);

private:
    QString m_code;
    QString m_name;
    float m_price;
    int m_quantity;
};

class InvoiceModel: public QAbstractListModel{
    Q_OBJECT

private:
    QList<InvoiceItem> m_invoice;

protected:
    QHash<int, QByteArray> roleNames() const;

public:
    enum InvoiceRole{
        CodeRole = Qt::UserRole + 1,
        NameRole,
        PriceRole,
        QuantityRole
    };

    InvoiceModel(QObject *parent = 0);
    void addInvoiceItem(const QString &code, const QString &name, const float &price);
    void removeInvoiceItem(const QString &code);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    float total();
    QJsonDocument invoiceJson();
    void clear();
};

class Invoice : public QObject
{
    Q_OBJECT
    Q_PROPERTY(InvoiceModel* model READ invoiceModel CONSTANT)
private:
    InvoiceModel* m_model;
    InvoiceModel* invoiceModel() const;
    Service service;
public:
    explicit Invoice(QObject *parent = nullptr);
    ~Invoice();

public slots:
    void addItemToInvoice(QString code, QString name, float price);
    void removeItemFromInvoice(QString code);
    void createInvoice();

signals:
    void invoiceItemChange(float total);
};

#endif // INVOICE_H
