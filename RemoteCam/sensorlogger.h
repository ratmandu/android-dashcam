#ifndef SENSORLOGGER_H
#define SENSORLOGGER_H

#include <QObject>

class SensorLogger : public QObject
{
  Q_OBJECT
public:
  explicit SensorLogger(QObject *parent = 0);

signals:

public slots:

};

#endif // SENSORLOGGER_H
