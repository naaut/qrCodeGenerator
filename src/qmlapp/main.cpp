#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickView>

#include <presentation/QrCodePresenter.h>
#include <usecase/GenerationUsecase.h>
#include <usecase/PrintingUsecase.h>
#include <core/Entity.h>
#include <core/Painter.h>

#include <qmlinjector/qmlinjector.h>
#include <qmlinjector/qmlinjectorbuilder.h>

#include "di/di.hpp"

namespace di = boost::di;

const char * const qmlPath = "qrc:/QmlInjectorCore/qml/main.qml";

int main(int argc, char *argv[])
{
    const auto injector = di::make_injector(
            di::bind<QrCodeUsecase>.to<QrCodeUsecase>(),
            di::bind<PrintingUsecase>.to<PrintingUsecase>()
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
    qmlRegisterType<Painter>("core", 1, 0, "Painter");

    engine.rootContext()->setContextObject(builder.build());
    engine.rootContext()->setContextProperty("$QmlEngine", &engine);
    qmlRegisterUncreatableType<ErrorCorrection>("entity", 1, 0, "ECL", "Not creatable as it is an enum type");

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
