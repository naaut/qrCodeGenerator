#include <qmlinjector/qmlinjector.h>
#include <qmlinjector/qmlobjectcreator.h>

#include <QQmlContext>
#include <QQmlEngine>

QmlInjector::QmlInjector(QQuickItem * parent)
	: QQuickItem(parent)
{
	setFlag(ItemIsFocusScope);
}

QmlInjector::~QmlInjector()
{
}

void QmlInjector::setContext(QVariant context)
{
	if (m_context == context)
		return;

	m_context = context;
	emit contextChanged();
}

void QmlInjector::sourceComponent(QQmlComponent * sourceComponent)
{
	if (m_sourceComponent == sourceComponent)
		return;
	m_sourceComponent = sourceComponent;
	emit sourceComponentChanged();
}

QQuickItem * QmlInjector::view() const
{
	return m_view;
}

void QmlInjector::componentComplete()
{
	QQuickItem::componentComplete();
	loadComponent();
}

void QmlInjector::loadComponent()
{
	if (m_sourceComponent == nullptr)
		return;

	QQmlEngine * engine = qmlEngine(this);
	QQmlContext * context = engine->rootContext();

	if (!context)
	{
		return;
	}

	QmlObjectCreator * creator = qobject_cast<QmlObjectCreator *>(context->contextObject());

	if (!creator)
	{
		qWarning() << "qmlInjector: Creator was not found";
		return;
	}

	if (QObject * obj = m_sourceComponent->beginCreate(context))
	{
		obj->setParent(this);
		obj->setProperty("injector", QVariant::fromValue(this));
		if (const auto metaObject = obj->metaObject())
		{
			for (int i = 0; i < metaObject->propertyCount(); ++i)
			{
				auto p = metaObject->property(i);
				if (p.name()[0] == '$')
				{
					QString typeName = p.typeName();
					if (p.isWritable())
					{
						QObject * value =
							creator->createObject(typeName.remove('*'), m_context).release();
						value->setParent(this);
						QVariant val = QVariant::fromValue(value);
						obj->setProperty(p.name(), val);
					}
				}
			}
		}
		else
		{
			qWarning() << "Can't find meta info";
		}
		m_view = static_cast<QQuickItem *>(obj);
		emit viewChanged();
		if (!m_view)
			return;
		m_view->setParentItem(this);
		m_sourceComponent->completeCreate();
	}
	else
	{
		qWarning() << "Can't create component";
	}
}
