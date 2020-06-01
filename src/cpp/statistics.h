#ifndef STATISTICS_H
#define STATISTICS_H

#include <QObject>
#include <QDateTime>
#include "service.h"

class Statistics : public QObject
{

    Q_OBJECT
private:
    Service service;
    void networkError();

public:
    explicit Statistics(QObject *parent = nullptr);

public slots:
    void loadStatistics(QDateTime date);

signals:
    void statisticsLoaded(float income, float expense);

};

#endif // STATISTICS_H
