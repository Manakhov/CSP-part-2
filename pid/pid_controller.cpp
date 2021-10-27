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

float pid_controller::getOutput()
{
    return c_1*x_1 + c_2*x_2 + d*prev_u;
}

float pid_controller::update(float u)
{
    float y = getOutput();
    float tmp_x_1 = x_1;
    float tmp_x_2 = x_2;
    x_1 = a_11*tmp_x_1 + a_12*tmp_x_2 + b_1*u;
    x_2 = a_21*tmp_x_1 + a_22*tmp_x_2 + b_2*u;
    prev_u = u;
    return y;
}

float pid_controller::filter(float f_u)
{
    float f_y = f_c*f_x;
    float f_tmp_x = f_x;
    f_x = f_a*f_tmp_x + f_b*f_u;
    f_prev_u = f_u;
    return f_y;
}

void pid_controller::getMessage(QByteArray byteArray)
{
    quint8 crc = 0;
    for (quint8 i = 0; i < byteArray.size(); ++i) {
        crc += byteArray[i];
    }
    if (crc != 0xFF) return;

    qDebug() << byteArray.toHex(' ');

    i++;
    float t = i/50;
    float data1;
    float data2;
    memcpy(&data1, byteArray.data() + 2, 4);
    memcpy(&data2, byteArray.data() + 6, 4);

    *m_stream << data1 << " " << data2 << "\n";
    qDebug() << data1 << " " << data2;


//    emit generatedReference(30 + 15 * std::cos(0.01 * i));
//    emit generatedReference(data2);
    emit generatedReference(70 - (10*std::exp(-0.1*t)*(-std::pow((t-2), 2) + 60*t)*std::sin(t/2))/100);
    emit generatedInput(update(data2 - filter(data1)));
}
