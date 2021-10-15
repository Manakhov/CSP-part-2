#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include <QObject>
#include <QDebug>

class pid_controller : public QObject
{
    Q_OBJECT
public:
    explicit pid_controller(QObject *parent = nullptr);

signals:

public slots:

    void getMessage(QByteArray byteArray);
};

#endif // PID_CONTROLLER_H
