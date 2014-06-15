#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QTcpSocket>
#include <QDataStream>
#include <QBuffer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  QImage *img;
  qint64 length;
  QTcpSocket *socket;
  QByteArray ba;
  QBuffer socketBuffer;
  QBuffer imageBuffer;
  QDataStream str;
  bool waitingForData;

private slots:
  void onReadyRead();
};

#endif // MAINWINDOW_H
