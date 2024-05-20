#pragma once

#include <QtCore/QHash>
#include <QtCore/QObject>
#include <QtCore/QVariant>

#include <functional>

using Creator = std::function<std::unique_ptr<QObject>(QVariant)>;
using Creators = QHash<QString, Creator>;

class QmlObjectCreator : public QObject
{
	Q_OBJECT

public:
	QmlObjectCreator(Creators && creators, QObject * parent = nullptr);

	std::unique_ptr<QObject> createObject(QString className, QVariant context = QVariant());

private:
	Creators m_creators;
};
