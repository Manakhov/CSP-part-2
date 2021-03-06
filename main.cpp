#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include "./lib/controllerbackend.h"

#include "pid/pid_controller.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    ControllerBackend controllerBackend(50, "Zsdnw82iuw");

    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.rootContext()->setContextProperty("plant", &controllerBackend);

    qDebug() << &engine;

    pid_controller controller;

    QObject::connect(&controllerBackend, &ControllerBackend::outputBytesChanged,
                     &controller, &pid_controller::getMessage);

    QObject::connect(&controller, &pid_controller::generatedReference,
                     &controllerBackend, &ControllerBackend::setReferenceSignal);

    QObject::connect(&controller, &pid_controller::generatedInput,
                     &controllerBackend, &ControllerBackend::setInput);

    engine.load(url);

    return app.exec();
}
