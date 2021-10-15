#include "pid_controller.h"

pid_controller::pid_controller(QObject *parent) : QObject(parent)
{
    m_file = new QFile(QDateTime::currentDateTime().toString("hh_mm_ss"));

    if (!m_file->open(QIODevice::WriteOnly)){
        qDebug() << "Failed";
    }

    m_stream = new QTextStream(m_file);
}

pid_controller::~pid_controller()
{
    m_file->close();

    delete m_file;
    delete m_stream;
}

void pid_controller::getMessage(QByteArray byteArray)
{
    qDebug() << byteArray.toHex(' ');

    i++;
    float data1;
    float data2;
    memcpy(&data1, byteArray.data() + 2, 4);
    memcpy(&data2, byteArray.data() + 6, 4);

    *m_stream << data1 << " " << data2 << "\n";
    qDebug() << data1 << " " << data2;

    quint8 crc = 0;
    for (quint8 i = 0; i < byteArray.size(); ++i) {
        crc += byteArray[i];
    }
    if (crc != 0xFF) return;

    emit generatedReference(50 + 25 * std::cos(0.01 * i));
    emit generatedInput((data2 - data1) * 5);
}
