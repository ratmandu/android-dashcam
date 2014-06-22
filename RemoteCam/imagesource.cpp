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

//  exposure->setFlashMode(QqCameraExposure::FlashVideoLight);
  exposure->setExposureMode(QCameraExposure::ExposureAuto);



  counter = 0;

  recorder = new QMediaRecorder(camera);
  camera->setCaptureMode(QCamera::CaptureVideo);
  if (probe->setSource(recorder)) {
    qDebug() << "Successfully set QMediaRecorder as source for QVideoProbe";
  }
  connect(probe, SIGNAL(videoFrameProbed(const QVideoFrame&)), this, SLOT(processFrame(QVideoFrame)));
  connect(&frameTimer, SIGNAL(timeout()), this, SLOT(frameTimerTick()));

//  camera->start();


  QVideoEncoderSettings settings = recorder->videoSettings();

  settings.setResolution(1920,1080);
  settings.setQuality(QMultimedia::VeryHighQuality);
  settings.setFrameRate(30.0);
  //settings.setCodec("video/mp4");

  recorder->setVideoSettings(settings);
  recorder->setContainerFormat("mp4");
  camera->setCaptureMode(QCamera::CaptureVideo);
  camera->start();

  frameTimer.start(1000);
  startRecording = true;

  //  qDebug() << recorder->containerFormat() << recorder->videoSettings().codec();
}

void ImageSource::newVideo()
{
  recorder->stop();
  QTimer::singleShot(300000, this, SLOT(newVideo()));
  recorder->setOutputLocation(QUrl::fromLocalFile(QString("/sdcard/DCIM/%1.mp4").arg(QDateTime::currentDateTime().toString(Qt::ISODate))));
  recorder->record();
}

void ImageSource::processFrame(QVideoFrame frame)
{
  qDebug() << recorder->duration();
  if (sendFrame) {
    if (frame.map(QAbstractVideoBuffer::ReadOnly)) {
      if (frame.pixelFormat() == QVideoFrame::Format_NV21) {
        QImage img(frame.size(), QImage::Format_RGB32);
        qt_convert_NV21_to_ARGB32((uchar*)frame.bits(), (quint32*)img.bits(), frame.width(), frame.height());
        img.save(QString("/sdcard/DCIM/DashCam/Images/%1.jpg").arg(QDateTime::currentDateTime().toString(Qt::ISODate)), "JPG");
        emit newFrame(img);
        qDebug() << "Saving Frame" << counter;
        sendFrame = false;
      }
      frame.unmap();
    }
  }

  if (startRecording) {
    QTimer::singleShot(300000, this, SLOT(newVideo()));
    recorder->setOutputLocation(QUrl::fromLocalFile(QString("/sdcard/DCIM/DashCam/Video/%1.mp4").arg(QDateTime::currentDateTime().toString(Qt::ISODate))));
    recorder->record();

    qDebug() << recorder->supportedResolutions();
    qDebug() << recorder->state();
    qDebug() << recorder->status();
    qDebug() << recorder->error();
    startRecording = false;
  }
}

void ImageSource::frameTimerTick()
{
  sendFrame = true;
//  qDebug() << "Frame";
}
