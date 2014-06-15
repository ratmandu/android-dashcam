#include "imageprovider.h"

QImage ImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
  if (size) {
    if (id == "front") {
      *size = QSize(frontImage.width(), frontImage.height());
    } else if (id == "rear") {
      *size = QSize(rearImage.width(), rearImage.height());
    }
  }

  if (id == "front") {
    return frontImage;
  } else if (id == "rear") {
    return rearImage;
  }
}

void ImageProvider::newImage(bool isFront, QImage image)
{
  if (isFront) {
    frontImage = image;
  } else {
    rearImage = image;
  }
  emit newFrameReady(isFront);
}
