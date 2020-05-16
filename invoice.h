#ifndef INVOICE_H
#define INVOICE_H

#include <QObject>
#include <QString>

class Invoice : public QObject
{
    Q_OBJECT
public:
    explicit Invoice(QObject *parent = nullptr);

public slots:
    void addItemToInvoice(QString code, QString name, float price);
    void createInvoice();

signals:

};

#endif // INVOICE_H
