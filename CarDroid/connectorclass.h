#ifndef CONNECTORCLASS_H
#define CONNECTORCLASS_H

#include <QObject>
#include <QDebug>

class ConnectorClass : public QObject
{
  Q_OBJECT
public:
  explicit ConnectorClass(QObject *parent = 0);
  Q_INVOKABLE void connectFrontServer(QString host);
  Q_INVOKABLE void connectRearServer(QString host);
  Q_INVOKABLE void findAndConnectFrontServer();
  Q_INVOKABLE void findAndConnectRearServer();

signals:
  void connectToFrontImageServer(QString host);
  void connectToRearImageServer(QString host);
  void findAndConnectFront();
  void findAndConnectRear();

public slots:

};

#endif // CONNECTORCLASS_H
