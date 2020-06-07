#ifndef PAGENAVIGATION_H
#define PAGENAVIGATION_H

#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>

class PageNavigation : public QObject
{
    Q_OBJECT
public:
    explicit PageNavigation(QObject *parent = nullptr);
    static PageNavigation *instance(QQmlEngine *engine, QJSEngine *scriptEngine){
        Q_UNUSED(engine);
        Q_UNUSED(scriptEngine);
        return new PageNavigation;
    }

public slots:
    void checkToken();

signals:
    void tokenLoaded(bool isTokenAvailable);

};

#endif // PAGENAVIGATION_H
