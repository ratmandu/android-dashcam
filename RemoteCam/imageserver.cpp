#include "imageserver.h"

ImageServer::ImageServer(QObject *parent) :
  QObject(parent)
{
  if (server.listen(QHostAddress::AnyIPv4, 2020))
    qDebug() << "Server started on port 2020";

  started = false;
  buffer.clear();
//  buf.open(QIODevice::ReadWrite);

  connect(&server, SIGNAL(newConnection()), this, SLOT(newConnection()));
}

void ImageServer::newFrame(QImage img)
{
//  if (!started)
//    return;

//  qDebug() << "Server received image";
  if (clients.count() == 0)
    return;

  QByteArray ba;
  QBuffer buf(&ba);
  img.save(&buf, "JPG", 80);
  qDebug() << ba.size();
  ba.append("Jiggle");
  //  qint64 length = sizeof(quint32) + buf.data().size();

  if (!clients.count())
    return;

  for (int i = 0; i < clients.count(); i++) {
    sending = true;
    if (!clients.at(i))
      return;
    clients.at(i)->write(ba);
    clients.at(i)->flush();
//    clients.at(i)->waitForBytesWritten(1000);
    sending = false;
  }
}

void ImageServer::newConnection()
{
  clients.append(server.nextPendingConnection());
  connect(clients.last(), SIGNAL(disconnected()), this, SLOT(removeConnection()));
  connect(clients.last(), SIGNAL(readyRead()), this, SLOT(readyRead()));
  qDebug() << "New connection!";
}

void ImageServer::removeConnection()
{
  waitTimer = 0;
  while (sending || ++waitTimer < 65530);

  QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

  if (!client)
    return;

  clients.removeAll(client);
  client->deleteLater();
}

void ImageServer::readyRead()
{
  qDebug() << "ReadyRead() called.";
  QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
  if (!client)
    return;

  buffer.append(client->readAll());

  if (buffer.contains("H\r\n")) {
    // send host name
    client->write(QHostInfo::localHostName().toUtf8());
    client->flush();
    client->waitForBytesWritten(1000);
    buffer.clear();
  }

  if (buffer.contains("S\r\n")) {
    started = true;
    buffer.clear();
  }
}
