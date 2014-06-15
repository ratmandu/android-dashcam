#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml/QQmlEngine>
#include <QtQML/QQmlContext>
#include <QtQuick/QQuickItem>
#include <QThread>

#include "imageclient.h"
#include "imageprovider.h"
#include "connectorclass.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ImageProvider *provider = new ImageProvider;
    ImageClient frontClient;
    ImageClient rearClient;
    QThread frontWorker;
    QThread rearWorker;

    frontClient.moveToThread(&frontWorker);
    rearClient.moveToThread(&rearWorker);
    frontWorker.start();
    rearWorker.start();

    qmlRegisterType<ConnectorClass>("ConnectorClass", 1, 0, "ConnectorClass");

    frontClient.setIsFront(true);
//    frontClient.connectToServer("192.168.1.123");
    rearClient.setIsFront(false);
//    rearClient.connectToServer("192.168.1.141");

    QObject::connect(&frontClient, SIGNAL(newFrame(bool,QImage)), provider, SLOT(newImage(bool,QImage)));
    QObject::connect(&rearClient, SIGNAL(newFrame(bool,QImage)), provider, SLOT(newImage(bool,QImage)));

    QQmlApplicationEngine engine;
    engine.addImageProvider(QLatin1String("Cameras"), provider);
//    engine.
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    QObject *rootObj = engine.rootObjects().first();
    QObject *connector = rootObj->findChild<QObject*>("connectorObject");
    qDebug() << rootObj << connector;
    if (connector) {
      qDebug() << "Connecting!";
      QObject::connect(connector, SIGNAL(connectToFrontImageServer(QString)), &frontClient, SLOT(connectToServer(QString)));
      QObject::connect(connector, SIGNAL(connectToRearImageServer(QString)), &rearClient, SLOT(connectToServer(QString)));
      QObject::connect(connector, SIGNAL(findAndConnectFront()), &frontClient, SLOT(findAndConnect()));
      QObject::connect(connector, SIGNAL(findAndConnectRear()), &rearClient, SLOT(findAndConnect()));

    }

    return app.exec();
}
