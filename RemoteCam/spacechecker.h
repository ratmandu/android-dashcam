#ifndef SPACECHECKER_H
#define SPACECHECKER_H

#include <QObject>
#include <QTimer>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QDateTime>
#include <QTextStream>
#include <QDebug>

#include <stdlib.h>

class SpaceChecker : public QObject
{
  Q_OBJECT
public:
  explicit SpaceChecker(QObject *parent = 0);

private:
  QTimer *timer;
  void deleteOldFiles();

signals:
  void freeSpace(double freeSpace);

public slots:
  void checkSpace();

};

#endif // SPACECHECKER_H
