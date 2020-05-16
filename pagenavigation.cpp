#include <QSettings>

#include "pagenavigation.h"
#include "programvariable.h"

PageNavigation::PageNavigation(QObject *parent) : QObject(parent)
{
    QSettings settting;
    QString token = settting.value("token", "").toString();
    if(token != ""){
        ProgramVariable::refreshToken = token;
        m_pageIndex = 2;
    }
    else {
        m_pageIndex = 1;
    }
}

