#ifndef ALARMKURALI_H
#define ALARMKURALI_H

#include "olcumler.h"
#include <QString>

class AlarmKurali
{
    public:
        virtual ~AlarmKurali() = default;

        virtual bool tetiklendiMi(const Olcumler &o) const = 0;

        virtual QString mesaj() const = 0;

};
class DusukOksijenKurali : public AlarmKurali
{
private:
    int esik;

public:
    //// (explicit) yanlışlıkla otomatik tip dönüşümü yapılmasın (ör. AlarmKurali *k = 90; gibi saçmalıklar derlenmesin).
    explicit DusukOksijenKurali (int esik = 90) : esik(esik){}

    bool tetiklendiMi(const Olcumler &o) const override{
        return o.spo2 < esik;
    }
    QString mesaj() const override{
        return QString("DÜŞÜK OKSİJEN - SpO₂ < %1").arg(esik);
    }

};

class TakipneKurali : public AlarmKurali
{
private:
    int esik;

public:
    explicit TakipneKurali(int esik = 25) : esik(esik){}

    bool tetiklendiMi(const Olcumler &o) const override {
        return o.hiz > esik;
    }
    QString mesaj() const override {
        return QString ("HIZLI SOLUNUM - Takipne > %1").arg(esik);
    }
};

class YuksekEtco2Kurali : public AlarmKurali
{
private:
    int esik;

public:
    explicit YuksekEtco2Kurali (int esik =47) : esik(esik){}

    bool tetiklendiMi(const Olcumler &o) const override {
        return o.etco2 > esik;
    }
    QString mesaj() const override {
        return QString("YÜKSEK CO₂ — EtCO₂ > %1").arg(esik);
    }

};

#endif // ALARMKURALI_H
