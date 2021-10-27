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
    float filter(float f_u);

signals:
    void generatedReference(float value);
    void generatedInput(float value);

public slots:

    void getMessage(QByteArray byteArray);

private:

    QFile* m_file;
    QTextStream* m_stream;

    quint16 i = 0;

    float a_11 = 0.6016;
    float a_12 = 0.0;
    float a_21 = 0.01568;
    float a_22 = 1.0;
    float b_1 = 0.5018;
    float b_2 = 0.005441;
    float c_1 = -46.21;
    float c_2 = 5.215;
    float d = 74.28;

    float x_1 = 0.0;
    float x_2 = 0.0;
    float prev_u = 0.0;

    float f_a = 0.8187;
    float f_b =0.07251;
    float f_c = 2.5;
    float f_d = 0.0;

    float f_x = 0.0;
    float f_prev_u = 0.0;

};

#endif // PID_CONTROLLER_H
