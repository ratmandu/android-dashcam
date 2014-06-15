#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  socket = new QTcpSocket();
  connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
  socket->connectToHost("192.168.1.123", 2020);
//  str = new QDataStream(socket);
  str.setDevice(socket);
  socketBuffer.open(QIODevice::ReadWrite);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::onReadyRead()
{
  socketBuffer.write(socket->readAll());
  if (socketBuffer.data().contains("Jiggle")) {
    socketBuffer.seek(0);
    img = new QImage;
    img->loadFromData(socketBuffer.buffer().mid(0, socketBuffer.data().indexOf("Jiggle")));
    qDebug() << img->size();
    socketBuffer.buffer().clear();
    ui->label->setPixmap(QPixmap::fromImage(*img));
  }
}
