#include "cizimwidget.h"

CizimWidget::CizimWidget(QWidget *parent)
    : QWidget(parent){}

// Şablon metot: ORTAK işi yapar, DEĞİŞEN işi alt sınıfa devreder.
void CizimWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter boya(this);

    boya.fillRect(rect(), zeminRengi);   // ① ORTAK iş: zemini çiz
    iceriCiz(boya);                      // ② POLİMORFİZM: hangi alt sınıfsa onun çizimi
}
