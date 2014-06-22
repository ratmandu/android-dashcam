#include "spacechecker.h"

SpaceChecker::SpaceChecker(QObject *parent) :
  QObject(parent)
{
  timer = new QTimer;
  connect(timer, SIGNAL(timeout()), this, SLOT(checkSpace()));
  timer->start(3000);
}

void SpaceChecker::deleteOldFiles()
{
//  QDir videoDir("/sdcard/DCIM/DashCam/Video");
  QDir videoDir;//("/Users/ratmandu/Pictures");
  videoDir.setPath("/Users/ratmandu");
  if (videoDir.count() > 1) {
    // delete oldest file
    videoDir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    videoDir.setSorting(QDir::Time | QDir::Reversed);

    QFileInfoList list = videoDir.entryInfoList();
    for (int i = 0; i < list.size(); i++) {
      QFileInfo fileinfo = list.at(i);
      qDebug() << fileinfo.absoluteFilePath() << fileinfo.size() << fileinfo.lastModified();
    }
  }
}

void SpaceChecker::checkSpace()
{
  QFile memFile;
  QStringList memLines;
  QStringList memColumns;

#ifdef __ANDROID__
  qDebug() << "Checking android free space";
  system("df /data > /sdcard/tmp.txt");
  memFile.setFileName("/sdcard/tmp.txt");
#elif __APPLE__ && __MACH__
  qDebug() << "checking osx free space";
  system("df -H / > /tmp/tmp.txt");
  memFile.setFileName("/tmp/tmp.txt");
#endif

  memFile.open(QIODevice::ReadOnly);

  QTextStream readData(&memFile);
  while (!readData.atEnd()) {
    memLines << readData.readLine();
  }

  memFile.close();
#ifdef __ANDROID__
  system("rm /sdcard/tmp.txt");
#elif __APPLE__ && __MACH__
  system("rm /tmp/tmp.txt");
#endif

  memColumns = memLines.at(1).split(QRegExp("\\s+"));
  memColumns.replaceInStrings("G", "");

  if (memColumns.at(3).toDouble() < 140) {
    qDebug() << "Clearing some space";
    deleteOldFiles();
  }

  emit freeSpace(memColumns.at(3).toDouble());
}
