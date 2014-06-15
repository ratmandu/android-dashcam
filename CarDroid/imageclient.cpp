#include "imageclient.h"

ImageClient::ImageClient(QObject *parent) :
  QObject(parent)
{
  connect(&socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
  socketBuffer.open(QIODevice::ReadWrite);
}

ImageClient::~ImageClient()
{
  socket.disconnectFromHost();
  socket.waitForDisconnected(3000);
}

void ImageClient::setIsFront(bool value)
{
  isFront = value;
}

void ImageClient::connectToServer(QString ip)
{
  qDebug() << "Requested connection to " << ip;
  socket.connectToHost(ip, 2020, QIODevice::ReadWrite);
  qDebug() << socket.state() << socket.errorString();
}

void ImageClient::findAndConnect()
{
  if (socket.isOpen()) {
    socket.disconnectFromHost();
  }

  for (int i = 1; i<255; i++) {
    qDebug() << i;
    socket.connectToHost(QString("192.168.49.%1").arg(i), 2020, QIODevice::ReadWrite);

    if (socket.waitForConnected(100) && socket.isOpen()) {
      socket.write("H\r\n");
      socket.flush();
//      while (socket.bytesAvailable() < 5);
      if (socket.waitForReadyRead(1000)) {
        qDebug() << socket.readAll();
        socket.write("S\r\n");
        socket.flush();
      }
    }
  }
}

void ImageClient::readyRead()
{
  socketBuffer.write(socket.readAll());
  if (socketBuffer.data().contains("Jiggle")) {
    socketBuffer.seek(0);
    image.loadFromData(socketBuffer.buffer().mid(0, socketBuffer.data().indexOf("Jiggle")));
    socketBuffer.buffer().clear();
    if (image.size() == QSize(0,0)) {
      return;
    }
    emit newFrame(isFront, image);
    qDebug() << "New Image!";
  }
}
