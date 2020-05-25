#ifndef EXPENSE_H
#define EXPENSE_H

#include <QObject>
#include <QString>

#include "service.h"

class Expense : public QObject
{
    Q_OBJECT

private:
    Service service;
    void networkError();


public:
    explicit Expense(QObject *parent = nullptr);

public slots:
    void createInvoice(QString item, float amount);

signals:
    void expenseCreated();

};

#endif // EXPENSE_H
