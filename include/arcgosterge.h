#ifndef ARCGOSTERGE_H
#define ARCGOSTERGE_H

#include "cizimwidget.h"
#include <QString>

// ============================================================
//  ArcGosterge — SARI YAY göstergesi.
//  Ortada büyük sayı, etrafında değere göre dolan sarı yay.
//  CizimWidget'tan TÜRER (kalıtım) → iceriCiz()'i override eder.
// ============================================================
class ArcGosterge : public CizimWidget
{
    Q_OBJECT
public:
    explicit ArcGosterge(QWidget *parent = nullptr);

    // göstergeyi tanımla: aralık + birim (ör. 21-100, "%")
    void ayarla(int alt, int ust, const QString &birim = QString());

public slots:
    void degeriAyarla(int yeniDeger);   // sensörden yeni değer gelince

protected:
    void iceriCiz(QPainter &boya) override;   // yay + sayı çizimi (polimorfizm)

private:
    int deger = 0;
    int alt   = 0;
    int ust   = 100;
    QString birim;
};

#endif // ARCGOSTERGE_H
