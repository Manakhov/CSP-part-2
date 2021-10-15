#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QDateTime>

#include <math.h>

class pid_controller : public QObject
{
    Q_OBJECT
public:
    explicit pid_controller(QObject *parent = nullptr);
    ~pid_controller();

signals:
    void generatedReference(float value);
    void generatedInput(float value);

public slots:

    void getMessage(QByteArray byteArray);

private:

    QFile* m_file;
    QTextStream* m_stream;

    quint16 i = 0;
};

#endif // PID_CONTROLLER_H
