#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>
#include <QNetworkReply>
#include <QSettings>
#include <QUrlQuery>
#include <QEventLoop>
#include <QString>
#include <QUrlQuery>

#include "programvariable.h"
#include "service.h"

Service::Service(QObject *parent): QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &Service::replyComplete);
}

void Service::addItem(QString name, QString alias, float price, QString color){
    QNetworkRequest request(QUrl(domain + "/api/item/"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", "Bearer " + getBearerToken().toUtf8());
    QJsonObject body {
        {"name", name},
        {"alias", alias},
        {"sellingPrice", price},
        {"color", color},
        {"images", QJsonArray()}
    };
    manager->post(request, QJsonDocument(body).toJson());
}

void Service::getItem(){
    QNetworkRequest request(QUrl(domain + "/api/item/"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", "Bearer " + getBearerToken().toUtf8());
    manager->get(request);
}

void Service::createInvoice(QJsonDocument invoices)
{
    QNetworkRequest request(QUrl(domain + "/api/invoice/"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", "Bearer " + getBearerToken().toUtf8());
    manager->post(request, invoices.toJson());
}

void Service::listInvoice(QString from, QString to)
{
    QUrl url(domain + "/api/invoice");
    std::initializer_list<QPair<QString, QString>> list = {
        QPair<QString, QString>("from", from),
        QPair<QString, QString>("to", to),
    };
    url.setQuery(QUrlQuery(list));
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", "Bearer " + getBearerToken().toUtf8());
    manager->get(request);
}

void Service::createExpense(QString item, float amount)
{
    QNetworkRequest request(QUrl(domain+"/api/expense"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", "Bearer " + getBearerToken().toUtf8());
    QJsonObject body {
        {"item", item},
        {"amount", amount}
    };
    manager->post(request, QJsonDocument(body).toJson());
}

void Service::listExpense(QString from, QString to)
{
    QUrl url(domain + "/api/expense");
    std::initializer_list<QPair<QString, QString>> list = {
        QPair<QString, QString>("from", from),
        QPair<QString, QString>("to", to),
    };
    url.setQuery(QUrlQuery(list));
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", "Bearer " + getBearerToken().toUtf8());
    manager->get(request);
}


void Service::replyComplete(QNetworkReply *reply){
    QVariant status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    int code = status.toInt();

    if(code == 0){
        emit networkError();
    }
    else{
        emit success(code, QJsonDocument::fromJson(reply->readAll()));
    }
    reply->deleteLater();
}

Service::~Service(){
    delete manager;
}

QString Service::bearerToken = "";
QString Service::getBearerToken(){
    if(bearerToken == ""){

        QString token = ProgramVariable::refreshToken;

        QUrl url("http://api.kadbyte.com/api/account/exchange");
        QUrlQuery query;
        query.addQueryItem("token", token);
        url.setQuery(query);
        QNetworkRequest request(url);

        QNetworkAccessManager bearerManager;
        QNetworkReply *reply = bearerManager.get(request);
        QEventLoop loop;
        QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        loop.exec();

        //Enclose this in a condition to check error.
        QJsonDocument body = QJsonDocument::fromJson(reply->readAll());
        bearerToken = body["token"].toString();
        reply->deleteLater();
        return bearerToken;
    }
    else
        return bearerToken;
}
