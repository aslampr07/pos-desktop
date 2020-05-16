#include <QDebug>
#include "invoice.h"

Invoice::Invoice(QObject *parent) : QObject(parent)
{

}

void Invoice::addItemToInvoice(QString code, QString name, float price)
{
    qDebug()<<code<<name<<price;
}

void Invoice::createInvoice()
{

}
