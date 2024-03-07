#include <qmlinjector/qmlobjectcreator.h>

QmlObjectCreator::QmlObjectCreator(Creators && creators, QObject * parent)
	: QObject(parent)
	, m_creators(std::move(creators))
{
}

std::unique_ptr<QObject> QmlObjectCreator::createObject(QString className, QVariant context)
{
	if (m_creators.contains(className))
	{
		return m_creators[className](context);
	}
	else
	{
		qCritical() << "No creator was found for " << className;
	}
	return {};
}
