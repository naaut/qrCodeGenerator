#include "Painter.h"

Painter::Painter(QQuickItem * parent)
    : QQuickPaintedItem{parent}
{}

void Painter::setImage(const QImage &image)
{
    m_image = image;
    update(); // Trigger a repaint
}

void Painter::paint(QPainter *painter)
{
    // Paint the image onto the item
    if (!m_image.isNull()) {
        painter->drawImage(boundingRect(), m_image);
    }
}



