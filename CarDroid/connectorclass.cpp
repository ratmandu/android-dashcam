#include "connectorclass.h"

ConnectorClass::ConnectorClass(QObject *parent) :
  QObject(parent)
{
}

void ConnectorClass::connectFrontServer(QString host)
{
  qDebug() << "Front!";
  emit connectToFrontImageServer(host);
}

void ConnectorClass::connectRearServer(QString host)
{
  qDebug() << "Rear!";
  emit connectToRearImageServer(host);
}

void ConnectorClass::findAndConnectFrontServer()
{
  qDebug() << "Find Front";
  emit findAndConnectFront();
}

void ConnectorClass::findAndConnectRearServer()
{
  qDebug() << "Find Rear";
  emit findAndConnectRear();
}
