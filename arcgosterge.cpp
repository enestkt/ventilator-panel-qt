#include "arcgosterge.h"
#include "yardimcilar.h"
#include <QDebug>

ArcGosterge::ArcGosterge(QWidget *parent)
    : CizimWidget(parent)
{
    zeminRengi = QColor("#f7f9fb");   // açık tema kartı (taban'dan miras üye)
    setMinimumSize(60, 60);
}

void ArcGosterge::ayarla(int a, int u, const QString &b)
{
    // GEÇERSİZ ARALIK KORUMASI
    // ust == alt olursa iceriCiz'deki (ust - alt) paydası sıfır olur.
    // double bölme olduğu için program çökmez, sessizce inf/NaN üretir;
    // asıl tehlike bir alt satırdaki int(tamYay * oran) — NaN'i int'e
    // çevirmek undefined behavior. Bozuk aralığı sınıfa hiç sokmuyoruz.
    if (u <= a) {
        qWarning() << "ArcGosterge::ayarla — gecersiz aralik:"
                   << a << u << "— yok sayildi";
        return;
    }

    alt = a;
    ust = u;
    birim = b;
    update();
}

void ArcGosterge::degeriAyarla(int yeniDeger)
{
    deger = yeniDeger;
    update();
}

void ArcGosterge::iceriCiz(QPainter &boya)
{
    boya.setRenderHint(QPainter::Antialiasing);

    // ortalanmış kare alan
    int kenar = qMin(width(), height()) - 8;
    QRectF alan((width() - kenar) / 2.0, (height() - kenar) / 2.0, kenar, kenar);

    double kalinlik = kenar * 0.12;
    QRectF yayAlani = alan.adjusted(kalinlik, kalinlik, -kalinlik, -kalinlik);

    const int baslangic = 225 * 16;    // sol-alt uç (yay burada başlar)
    const int tamYay    = -270 * 16;   // saat yönünde 270° (altta boşluk)

    // 1) arka plan yayı (gri iz)
    boya.setPen(QPen(QColor("#dbe2ea"), kalinlik, Qt::SolidLine, Qt::FlatCap));
    boya.drawArc(yayAlani, baslangic, tamYay);

    // 2) değer yayı (sarı) — orana göre dolar
    // Kırpmayı elle yazmak yerine yardimcilar.h'daki araliktaTut'u kullanıyoruz
    // (inline + call by value). DİKKAT: kırpılan şey sadece YAYIN oranı;
    // aşağıdaki drawText ham "deger"i yazar. Aralık dışına taşan gerçek ölçüm
    // ekranda gizlenmemeli — 65'lik SpO2'yi 70 göstermek hasta güvenliği sorunudur.
    double oran = double(araliktaTut(deger, alt, ust) - alt) / (ust - alt);
    boya.setPen(QPen(QColor("#f4b400"), kalinlik, Qt::SolidLine, Qt::FlatCap));
    boya.drawArc(yayAlani, baslangic, int(tamYay * oran));

    // 3) ortadaki büyük sayı
    boya.setPen(QColor("#1c2733"));
    QFont sf = boya.font();
    sf.setPointSizeF(kenar * 0.22);
    sf.setBold(true);
    boya.setFont(sf);
    boya.drawText(alan, Qt::AlignCenter, QString::number(deger));

    // 4) birim (küçük, sayının altında)
    if (!birim.isEmpty()) {
        QFont bf = boya.font();
        bf.setPointSizeF(kenar * 0.10);
        bf.setBold(false);
        boya.setFont(bf);
        boya.setPen(QColor("#7d8590"));
        QRectF birimAlani(alan.left(), alan.center().y() + kenar * 0.16,
                          alan.width(), kenar * 0.16);
        boya.drawText(birimAlani, Qt::AlignHCenter | Qt::AlignTop, birim);
    }
}
