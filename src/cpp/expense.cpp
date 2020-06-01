#include <QDebug>
#include <QJsonDocument>
#include "expense.h"


Expense::Expense(QObject *parent) : QObject(parent)
{
    connect(&service, &Service::networkError, this, &Expense::networkError);
}

void Expense::createInvoice(QString item, float amount)
{
    if(!buttonLock){
        buttonLock = true;
        if(item != "" && amount != 0){
            service.createExpense(item, amount);
            connect(&service, &Service::success, this, [=](int status, QJsonDocument body){
                 disconnect(&service, &Service::success, nullptr, nullptr);
                if(status == 200){
                    emit expenseCreated();
                    buttonLock = false;
                }
            });
        }
        else {
            buttonLock = false;
        }
    }
}

void Expense::networkError()
{
    buttonLock = false;
    qDebug()<<"Network error";
}
