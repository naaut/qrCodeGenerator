#pragma once

#include <QObject>
#include <QQuickPaintedItem>
#include <QImage>
#include <QPainter>


class Painter : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit Painter(QQuickItem * parent = nullptr);

    Q_INVOKABLE void setImage(const QImage& image);

    void paint(QPainter *painter) override;

signals:

private:
    QImage m_image;
};
