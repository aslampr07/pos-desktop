#include <QDebug>
#include <QDateTime>
#include <QTimeZone>
#include <QJsonArray>
#include <QJsonObject>
#include "statistics.h"

Statistics::Statistics(QObject *parent) : QObject(parent)
{
    connect(&service, &Service::networkError, this, &Statistics::networkError);
}

void Statistics::loadStatistics(QDateTime date)
{
    float incomeAmount = 0.0;
    float expenseAmount = 0.0;

    date.setTime(QTime(0, 0, 0, 0));
    QString from = date.toUTC().toString(Qt::DateFormat::ISODateWithMs);
    date.setTime(QTime(23, 59, 59, 999));
    QString to = date.toUTC().toString(Qt::DateFormat::ISODateWithMs);

    service.listInvoice(from, to);
    connect(&service, &Service::success, this, [=](int status, QJsonDocument body) mutable {
        disconnect(&service, &Service::success, nullptr, nullptr);
        if(status == 200){
            QJsonArray invoices = body.array();
            for(int i = 0; i < invoices.size(); i++){
                QJsonObject item = invoices[i].toObject();
                incomeAmount += item["amount"].toDouble();;
            }
        }
        service.listExpense(from, to);
        connect(&service, &Service::success, this, [=](int status, QJsonDocument body) mutable {
            disconnect(&service, &Service::success, nullptr, nullptr);
            if(status == 200){
                QJsonArray expenses = body.array();
                for(int i = 0; i < expenses.size(); i++){
                    QJsonObject item = expenses[i].toObject();
                    expenseAmount += item["amount"].toDouble();;
                }
                qDebug()<<incomeAmount<<":  "<<expenseAmount;
                emit statisticsLoaded(incomeAmount, expenseAmount);
            }
        });
    });
}


void Statistics::networkError()
{
    qDebug()<<"Hello World";
}
