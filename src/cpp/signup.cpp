#include <iostream>
#include <QDebug>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QByteArray>
#include <QNetworkRequest>
#include <QTextCodec>
#include <QJsonDocument>
#include <QSettings>

#include "programvariable.h"
#include "signup.h"

SignUp::SignUp(QObject *parent) : QObject(parent)
{

}

void SignUp::signup(){

    bool ok = true;

    if(m_username == ""){
        ok = false;
        emit userNameError("Username is empty");
    }
    if(m_password == ""){
        ok = false;
        emit passwordError("Password is empty");
    }

    if(ok){

        QNetworkRequest request(QUrl("http://api.kadbyte.com/api/account/login"));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QJsonObject body {
            {"username", m_username},
            {"password", m_password}
        };

        QNetworkAccessManager* manager = new QNetworkAccessManager(this);
        connect(manager, &QNetworkAccessManager::finished, this, &SignUp::replyFinished);
        manager->post(request, QJsonDocument(body).toJson());
    }
}

void SignUp::replyFinished(QNetworkReply *reply){
    int x = reply->error();
    qDebug()<<"error code"<< x;
    QVariant status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    int code = status.toInt();
    if(code == 200){
        QByteArray array = reply->readAll();
        QJsonDocument document = QJsonDocument::fromJson(array);
        QJsonObject body = document.object();
        QString token = body["token"].toString();

        ProgramVariable::refreshToken = token;
        if(m_IsRememberOn){
            QSettings settings;
            settings.setValue("token", token);
        }
        emit success();
    }
    else {
        qDebug()<<"Error occured"<<code;
    }
    reply->deleteLater();
}
