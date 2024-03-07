#pragma once

#include "qmlobjectcreator.h"
#include "qqml.h"

#include <QDebug>

class QmlInjectorBuilder
{
public:
	template <typename T> void add(Creator c)
	{
		QString type(T::staticMetaObject.className());
		m_creators.insert(type.remove("*"), std::move(c));
		qmlRegisterType<T>("presenters", 1, 0, T::staticMetaObject.className());
		qDebug() << "InjectorBuilder: registered "
				 << "presenters." << T::staticMetaObject.className();
	}

	QmlObjectCreator * build()
	{
		return new QmlObjectCreator(std::move(m_creators));
	}

private:
	QHash<QString, Creator> m_creators;
};
