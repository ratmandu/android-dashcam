#ifndef IMAGESERVER_H
#define IMAGESERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostInfo>
#include <QList>
#include <QImage>
#include <QBuffer>

#include "imagesource.h"

class ImageServer : public QObject
{
  Q_OBJECT
public:
  explicit ImageServer(QObject *parent = 0);
  Q_INVOKABLE void newFrame(QImage img);

private:
  QTcpServer server;
  QList<QTcpSocket*> clients;
  bool sending;
  bool started;
  int waitTimer;
  QByteArray buffer;
//  QBuffer buf;

signals:

public slots:

private slots:
  void newConnection();
  void removeConnection();
  void readyRead();
};

#endif // IMAGESERVER_H
