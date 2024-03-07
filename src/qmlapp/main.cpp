#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <presentation/QrCodePresenter.h>
#include <usecase/QrCodeUsecase.h>

#include <qmlinjector/qmlinjector.h>
#include <qmlinjector/qmlinjectorbuilder.h>

#include "di/di.hpp"

namespace di = boost::di;

const char * const qmlPath = "qrc:/QmlInjectorCore/qml/main.qml";

int main(int argc, char *argv[])
{
    const auto injector = di::make_injector(
            di::bind<QrCodeUsecase>.to<QrCodeUsecase>()
        );

    QmlInjectorBuilder builder;

    builder.add<QrCodePresenter>(
        [&injector](const QVariant &)
        {
            return injector.create<QrCodePresenterUnq>();
        });

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<QmlInjector>("injector", 1, 0, "QmlInjector");

    engine.rootContext()->setContextObject(builder.build());
    engine.rootContext()->setContextProperty("$QmlEngine", &engine);

    app.setOrganizationName("sednev");
    app.setOrganizationDomain("net");

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(QUrl(qmlPath));

    return app.exec();
}
