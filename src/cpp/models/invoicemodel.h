#ifndef INVOICEMODEL_H
#define INVOICEMODEL_H

#include<QObject>
#include<QAbstractListModel>
#include<QJsonDocument>
#include<QJsonArray>
#include<QJsonObject>

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
    QVector<InvoiceItem> m_invoice;
    int currentPage = 0;

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

public slots:
    void tabChanges(int index);


};
#endif // INVOICEMODEL_H
