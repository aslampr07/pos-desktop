#ifndef SIGNUP_H
#define SIGNUP_H

#include <QObject>
#include <QNetworkReply>

class SignUp : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString username MEMBER m_username)
    Q_PROPERTY(QString password MEMBER m_password)
    Q_PROPERTY(bool isRemeberEnabled MEMBER m_IsRememberOn);
public:
    explicit SignUp(QObject *parent = nullptr);

public slots:
    void signup();

signals:
    void userNameError(QString error);
    void passwordError(QString error);

private:
    QString m_username;
    QString m_password;
    bool m_IsRememberOn;
    void replyFinished(QNetworkReply* reply);
};

#endif // SIGNUP_H
