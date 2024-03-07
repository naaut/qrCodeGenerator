#pragma once

#include <QQmlComponent>
#include <QQmlParserStatus>
#include <QQuickItem>

class QmlInjector : public QQuickItem
{
	Q_OBJECT

	Q_PROPERTY(QVariant context READ context WRITE setContext NOTIFY contextChanged FINAL)
	Q_PROPERTY(QQmlComponent * sourceComponent READ sourceComponent WRITE sourceComponent NOTIFY
				   sourceComponentChanged FINAL)
	Q_PROPERTY(QQuickItem * view READ view NOTIFY viewChanged FINAL)

public:
	explicit QmlInjector(QQuickItem * parent = nullptr);
	~QmlInjector();

	QVariant context() const
	{
		return m_context;
	}
	QQmlComponent * sourceComponent() const
	{
		return m_sourceComponent;
	}

	void setContext(QVariant context);
	void sourceComponent(QQmlComponent * sourceComponent);
	QQuickItem * view() const;

	// QQmlParserStatus interface
public:
	void componentComplete() override;

signals:
	void contextChanged();
	void sourceComponentChanged();
	void viewChanged();

private:
	void loadComponent();

private:
	QVariant m_context;
	QQmlComponent * m_sourceComponent = nullptr;
	QQuickItem * m_view = nullptr;
};
