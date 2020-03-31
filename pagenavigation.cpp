#include <QSettings>
#include "pagenavigation.h"

PageNavigation::PageNavigation(QObject *parent) : QObject(parent)
{
    QSettings settting;
    QString token = settting.value("token", "").toString();
    if(token != ""){
        m_pageIndex = 2;
    }
    else {
        m_pageIndex = 1;
    }
}

