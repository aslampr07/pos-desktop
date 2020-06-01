#include <QtDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVector>

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
                disconnect(&service, &Service::success, nullptr, nullptr);
                if(status == 200){
                    emit itemInsertSuccess(isSaveNew);
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

void Item::loadItemList(){
    service.getItem();
    connect(&service, &Service::success, this, [=](int status, QJsonDocument body){
        disconnect(&service, &Service::success, nullptr, nullptr);
        if(status == 200){
            QJsonArray itemArray = body.array();
            QList<Product*> productList;
            for(int i = 0; i < itemArray.size(); i++){
                QString name = itemArray[i].toObject()["name"].toString();
                QString alias = itemArray[i].toObject()["alias"].toString();
                QString code = itemArray[i].toObject()["itemCode"].toString();
                double price = itemArray[i].toObject()["sellingPrice"].toDouble();
                QString date = itemArray[i].toObject()["createdAt"].toString();
                productList.append(new Product(i+1, code, name, alias, price, date));
            }
            emit itemListFetched(productList);
        }
    });
}

void Item::networkError(){
    qDebug()<<"Network signal triggered";
}


Product::Product(QObject *parent) : QObject(parent)
{

}

Product::Product(int slNumber, QString &code, QString &name, QString &alias, double &price, QString &createdAt, QObject *parent) :
    QObject(parent), m_slNumber(slNumber), m_code(code), m_name(name), m_alias(alias), m_price(price), m_createdAt(createdAt)
{

}
