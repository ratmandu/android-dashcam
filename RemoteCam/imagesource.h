#ifndef IMAGESOURCE_H
#define IMAGESOURCE_H

#include <QObject>
#include <QImage>
#include <QDebug>
#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>
#include <QCamera>
#include <QCameraFocus>
#include <QCameraExposure>
#include <QMediaRecorder>
#include <QVideoProbe>
#include <QBuffer>
#include <QTimer>
#include <QUrl>
#include <QDateTime>

#include "qandroidmultimediautils.h"

class ImageSource : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QAbstractVideoSurface *videoSurface READ videoSurface WRITE setVideoSurface)

public:
  explicit ImageSource(QObject *parent = 0);
  QAbstractVideoSurface* videoSurface() const { return m_surface; }

  Q_INVOKABLE void setVideoSurface(QAbstractVideoSurface *surface)
  {
    m_surface = surface;
    if (m_surface) {
      m_surface->start(m_format);
      camera->setViewfinder(m_surface);
    }
  }

private:
  QSize ImageSize;
  QImage outputImage;
  QAbstractVideoSurface *m_surface;
  QVideoSurfaceFormat m_format;
  QCamera *camera;
  QCameraFocus *focus;
  QCameraExposure *exposure;
  QMediaRecorder *recorder;
  QVideoProbe *probe;
  int counter;
  QTimer frameTimer;
  bool sendFrame;
  bool startRecording;

signals:
  void newFrame(QImage frame);

public slots:
  void newVideo();
  void onNewVideoContentReceived(const QVideoFrame &frame)
  {
    if (m_surface)
      m_surface->present(frame);
  }

  void processFrame(QVideoFrame frame);

private slots:
  void frameTimerTick();
};

#endif // IMAGESOURCE_H
