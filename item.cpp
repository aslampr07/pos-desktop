#include <QtDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "item.h"


Item::Item(QObject *parent) : QObject(parent)
{
    connect(&service, &Service::networkError, this, &Item::networkError);
}

void Item::createItem(QString name, QString alias, float price, bool isSaveNew){

        bool isOk = true;

        if(name == ""){
            isOk = false;
            emit nameInputError("Please enter a name");
        }

        if(alias == ""){
            isOk = false;
            emit aliasInputError("Please enter an alias");
        }

        if(isOk){
            service.addItem(name, alias, price, "ffffff");
            connect(&service, &Service::success, this, [=](int status, QJsonDocument body){
                if(status == 200){
                    emit success(isSaveNew);
                }
                else {
                     QJsonArray errors = body.array();
                     for(int i = 0; i < errors.size(); i++){
                         QJsonObject error = errors[i].toObject();
                         int errorCode = error["code"].toInt();
                         QString field = error["field"].toString();
                         if(errorCode == 10001){
                             emit aliasInputError("Alias already exists, please use another");
                         }
                         if(errorCode == 10013){
                             emit aliasInputError("Alias must be between 3 to 16 characters");
                         }
                     }
                }
            });
        }

}

void Item::networkError(){
    qDebug()<<"Network signal triggered";
}
