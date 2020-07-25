#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

#include "invoice.h"
#include "service.h"

Invoice::Invoice(QObject *parent) : QObject(parent)
{
    m_model = new InvoiceModel();
    m_tabmodel = new InvoiceTabModel();
    //Connect the tab with invoice, to notifiy that tab is switched
    connect(m_tabmodel, &InvoiceTabModel::tabChanged, m_model, &InvoiceModel::tabChanges);
}

Invoice::~Invoice()
{
    delete m_model;
    delete m_tabmodel;
}

void Invoice::addItemToInvoice(QString code, QString name, float price)
{
    m_model->addInvoiceItem(code, name, price);
    emit invoiceItemChange(m_model->total());
}

void Invoice::removeItemFromInvoice(QString code)
{
    m_model->removeInvoiceItem(code);
    emit invoiceItemChange(m_model->total());
}

void Invoice::createInvoice()
{
    if(!saveButtonLock){
        saveButtonLock = true;
        QJsonDocument invoiceJson = m_model->invoiceJson();
        if(invoiceJson.array().size() > 0){
            service.createInvoice(invoiceJson);
            connect(&service, &Service::success, this, [=](int status, QJsonDocument body){
                disconnect(&service, &Service::success, nullptr, nullptr);
                qDebug()<<status;
                if(status == 200){
                    m_model->clear();
                    emit invoiceItemChange(m_model->total());
                    saveButtonLock = false;
                }
            });
        }
        else {
            saveButtonLock = false;
        }
    }
}

void Invoice::tabItemClicked(int index)
{
    m_tabmodel->changeTab(index);
}

InvoiceModel *Invoice::invoiceModel() const
{
    return m_model;
}

InvoiceTabModel *Invoice::invoiceTabModel() const
{
    return m_tabmodel;
}
