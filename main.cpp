#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "signup.h"
#include "item.h"
#include "pagenavigation.h"
#include "invoice.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("Kadbyte");
    QCoreApplication::setOrganizationDomain("kadbyte.com");
    QCoreApplication::setApplicationName("pos");

    QGuiApplication app(argc, argv);

    qmlRegisterType<SignUp>("com.kadbyte.signup", 1, 0, "SignUp");
    qmlRegisterType<Item>("com.kadbyte.item", 1, 0, "Item");
    qmlRegisterType<Invoice>("com.kadbyte.invoice", 1, 0, "Invoice");
    qmlRegisterSingletonType<PageNavigation>("com.kadbyte.navigation", 1, 0, "Navigation", &PageNavigation::instance);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
