#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickItem>

#include "imagesource.h"
#include "imageserver.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<ImageSource>("ImageSource", 1, 0, "ImageSource");
    qmlRegisterType<ImageServer>("ImageServer", 1, 0, "ImageServer");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));


    return app.exec();
}
