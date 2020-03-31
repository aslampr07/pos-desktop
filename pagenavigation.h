#ifndef PAGENAVIGATION_H
#define PAGENAVIGATION_H

#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>

class PageNavigation : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int pageIndex MEMBER m_pageIndex)
public:
    explicit PageNavigation(QObject *parent = nullptr);
    static PageNavigation *instance(QQmlEngine *engine, QJSEngine *scriptEngine){
        Q_UNUSED(engine);
         Q_UNUSED(scriptEngine);
         return new PageNavigation;
    }
private:
    int m_pageIndex;

signals:

};

#endif // PAGENAVIGATION_H
