#include "pid_controller.h"

pid_controller::pid_controller(QObject *parent) : QObject(parent)
{
    qDebug() << sizeof(char);
    qDebug() << sizeof(quint8);
    qDebug() << sizeof(quint16);
    qDebug() << sizeof(int);
    qDebug() << sizeof(float);
    qDebug() << sizeof(double);
}

void pid_controller::getMessage(QByteArray byteArray)
{
    qDebug() << byteArray.toHex(' ');

    float data1;
    float data2;
    memcpy(&data1, byteArray.data() + 2, 4);
    memcpy(&data2, byteArray.data() + 6, 4);

    qDebug() << data1 << " " << data2;
}
