#ifndef IMAGECLIENT_H
#define IMAGECLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QHostInfo>
#include <QImage>
#include <QBuffer>

class ImageClient : public QObject
{
  Q_OBJECT
public:
  explicit ImageClient(QObject *parent = 0);
  ~ImageClient();
  void setIsFront(bool value);

private:
  QTcpSocket socket;
  QImage image;
  QBuffer socketBuffer;
  bool isFront;

signals:
  void newFrame(bool value, QImage frame);

public slots:
  void connectToServer(QString ip);
  void findAndConnect();

private slots:
  void readyRead();

};

#endif // IMAGECLIENT_H
