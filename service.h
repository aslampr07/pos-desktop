#ifndef SERVICE_H
#define SERVICE_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QJsonDocument>

class Service: public QObject
{
    Q_OBJECT
    
    const QString domain = "http://api.kadbyte.com";
    QNetworkAccessManager *manager;
    void replyComplete(QNetworkReply *reply);

public:
    explicit Service(QObject *parent = nullptr);
    ~Service();

    static QString bearerToken;
    static QString getBearerToken();

    // POST /api/item
    void addItem(QString name, QString alias, float price, QString color);
    // GET /api/item
    void getItem();

signals:
    void success(int status, QJsonDocument body);
    void networkError();
};

#endif // SERVICE_H
