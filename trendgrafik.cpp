#include "trendgrafik.h"
#include <QPainter>

TrendGrafik::TrendGrafik(QWidget *parent)
    : CizimWidget(parent)
{
    setMinimumHeight(45);
}

void TrendGrafik::degerEkle(int deger)
{
    degerler.append(deger);
    while(degerler.size()>60)
        degerler.removeFirst();

    update();
}

int TrendGrafik::yKoordinati(int deger) const
{
    const int minDeger=5, maxDeger=40;

    double oran = double (deger-minDeger) / (maxDeger-minDeger);

    return height() - int(oran * height());
}
void TrendGrafik::iceriCiz(QPainter &boya)
{
    int alarmY = yKoordinati(25);
    boya.setPen(QPen(Qt::red ,1, Qt::DashLine));
    boya.drawLine(0, alarmY, width(), alarmY);

    if(degerler.size()<2)
        return;

    boya.setPen(QPen(Qt::green, 2));
    double xAdim = width() / 59.0;

    for (int i = 1; i < degerler.size(); ++i) {
        int x1 = int((i-1) * xAdim);
        int y1 = yKoordinati(degerler[i-1]);
        int x2 = int(i * xAdim);
        int y2 = yKoordinati(degerler[i]);
        boya.drawLine(x1,y1,x2,y2);

    }
}
