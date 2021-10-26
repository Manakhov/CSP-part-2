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

    float getOutput();
    float update(float u);

signals:
    void generatedReference(float value);
    void generatedInput(float value);

public slots:

    void getMessage(QByteArray byteArray);

private:

    QFile* m_file;
    QTextStream* m_stream;

    quint16 i = 0;

    float a_11 = 0.9141;
    float a_12 = 0.0;
    float a_21 = 0.01913;
    float a_22 = 1.0;
    float b_1 = 0.153;
    float b_2 = 0.001553;
    float c_1 = -3.296;
    float c_2 = 3.005;
    float d = 20.3;

    float x_1 = 0.0;
    float x_2 = 0.0;
    float prev_u = 0.0;

};

#endif // PID_CONTROLLER_H
