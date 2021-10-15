#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QDateTime>

class pid_controller : public QObject
{
    Q_OBJECT
public:
    explicit pid_controller(QObject *parent = nullptr);
    ~pid_controller();

signals:

public slots:

    void getMessage(QByteArray byteArray);

private:

    QFile* m_file;
    QTextStream* m_stream;
};

#endif // PID_CONTROLLER_H
