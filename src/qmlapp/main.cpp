#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickView>

#include <domain/IHistoryDataProvider.h>
#include <data/HistoryDataProvider.h>

#include <presentation/HistoryPresenter.h>
#include <presentation/QrCodePresenter.h>
#include <presentation/SettingsPresenter.h>
#include <presentation/HistoryModel.h>
#include <usecase/GenerationUsecase.h>
#include <usecase/HistoryUsecase.h>
#include <usecase/SettingsUsecase.h>
#include <core/Painter.h>

#include <qmlinjector/qmlinjector.h>
#include <qmlinjector/qmlinjectorbuilder.h>

#include "di/di.hpp"

namespace di = boost::di;

const char * const qmlPath = "qrc:/QrCodeGeneratorBuild/qml/main.qml";

int main(int argc, char *argv[])
{
	const auto injector = di::make_injector(
		di::bind<QrCodeUsecase>.to<QrCodeUsecase>(),
		di::bind<SettingsUsecase>.to<SettingsUsecase>(),
		di::bind<HistoryUsecase>.to<HistoryUsecase>(),
		di::bind<domain::IHistoryDataProvider>.to<data::HistoryDataProvider>()
	);

	QmlInjectorBuilder builder;

	builder.add<QrCodePresenter>(
				[&injector](const QVariant &) {
		return injector.create<QrCodePresenterUnq>();
	});

	builder.add<SettingsPresenter>(
				[&injector](const QVariant &) {
		return injector.create<SettingsPresenterUnq>();
	});

	builder.add<HistoryPresenter>(
				[&injector](const QVariant &) {
		return injector.create<HistoryPresenterUnq>();
	});

	QGuiApplication app(argc, argv);

	QQmlApplicationEngine engine;
	qmlRegisterType<QmlInjector>("injector", 1, 0, "QmlInjector");
	qmlRegisterType<HistoryModel>("presenters", 1, 0, "HistoryModel");
	qmlRegisterType<Painter>("core", 1, 0, "Painter");

	engine.rootContext()->setContextObject(builder.build());
	engine.rootContext()->setContextProperty("$QmlEngine", &engine);
	qmlRegisterUncreatableType<domain::ErrorCorrection>("entity", 1, 0, "ECL", "Not creatable as it is an enum type");
	qmlRegisterUncreatableType<domain::QrCode>("entity", 1, 0, "QrCodeType", "Not creatable as it is an enum type");

	app.setOrganizationName("sednev.net");
	app.setOrganizationDomain("sednev.net");
	app.setApplicationName("QrCode Generator");

	QObject::connect(
		&engine,
		&QQmlApplicationEngine::objectCreationFailed,
		&app,
		[]() { QCoreApplication::exit(-1); },
		Qt::QueuedConnection);

	engine.loadFromModule("net.sednev.qrcodegenerator", "Main");

	return app.exec();
}
