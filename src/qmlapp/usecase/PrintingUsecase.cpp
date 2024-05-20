#include "PrintingUsecase.h"

#include <QtGui/QPainter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>


PrintingUsecase::PrintingUsecase()
{}

void PrintingUsecase::printQRCode(const QImage &qrImage)
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog printDialog(&printer);

    if (printDialog.exec() == QDialog::Accepted) {
        QPainter painter(&printer);

        // Scale the image to fit within the printer's page.
        QRect rect = painter.viewport();
        QSize size = qrImage.size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(qrImage.rect());

        // Print the image.
        painter.drawImage(0, 0, qrImage);
    }
}
