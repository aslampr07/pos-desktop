#include <QSettings>
#include <QDebug>

#include "pagenavigation.h"
#include "programvariable.h"

PageNavigation::PageNavigation(QObject *parent) : QObject(parent)
{

}

void PageNavigation::checkToken()
{
    QSettings settting;
    QString token = settting.value("token", "").toString();
    if(token != ""){
        ProgramVariable::refreshToken = token;
        emit tokenLoaded(true);
    }
    else {
        emit tokenLoaded(false);
    }
}

