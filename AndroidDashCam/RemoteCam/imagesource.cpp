#include "imagesource.h"

ImageSource::ImageSource(QObject *parent) :
  QObject(parent)
{
  camera = new QCamera(QCamera::BackFace, this);
  probe = new QVideoProbe(this);
  focus = camera->focus();
  exposure = camera->exposure();

  focus->setFocusMode(QCameraFocus::ContinuousFocus);
  focus->setFocusPointMode(QCameraFocus::FocusPointAuto);

  exposure->setFlashMode(QCameraExposure::FlashOn);

  counter = 0;

  camera->setCaptureMode(QCamera::CaptureStillImage);
  if (probe->setSource(camera)) {
    qDebug() << "Successfully set QCamera as source for QVideoProbe";
  }
  connect(probe, SIGNAL(videoFrameProbed(const QVideoFrame&)), this, SLOT(processFrame(QVideoFrame)));
  connect(&frameTimer, SIGNAL(timeout()), this, SLOT(frameTimerTick()));

  camera->start();
  frameTimer.start(1000/20);
}

void ImageSource::processFrame(QVideoFrame frame)
{
  if (sendFrame) {
    if (frame.map(QAbstractVideoBuffer::ReadOnly)) {
      if (frame.pixelFormat() == QVideoFrame::Format_NV21) {
        QImage img(frame.size(), QImage::Format_RGB32);
        qt_convert_NV21_to_ARGB32((uchar*)frame.bits(), (quint32*)img.bits(), frame.width(), frame.height());
//        img.save(QString("/sdcard/DCIM/Camera/img%1.jpg").arg(++counter), "JPG");
        emit newFrame(img);
//        qDebug() << "Saving Frame" << counter;
        sendFrame = false;
      }
      frame.unmap();
    }
  }
}

void ImageSource::frameTimerTick()
{
  sendFrame = true;
//  qDebug() << "Frame";
}
