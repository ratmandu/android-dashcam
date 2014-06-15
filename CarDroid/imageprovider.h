#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <QQuickItem>
#include <QObject>

#include "imageclient.h"

class ImageProvider : public QObject, public QQuickImageProvider
{
Q_OBJECT
public:
  explicit ImageProvider() : QQuickImageProvider(QQuickImageProvider::Image) {
  }

  QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);

private:
  QImage frontImage;
  QImage rearImage;

signals:
  Q_SIGNAL void newFrameReady(bool isFrontImage);

public slots:
  void newImage(bool isFront, QImage image);
};

#endif // IMAGEPROVIDER_H
