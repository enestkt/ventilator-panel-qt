#ifndef ALARMDEGERLENDIRICI_H
#define ALARMDEGERLENDIRICI_H

#include "alarmkurali.h"
#include <memory>
#include <vector>

// ============================================================
//  AlarmDegerlendirici — kural listesini tutar, sirayla dener,
//  ilk tetiklenen kuralin mesajini dondurur.
//
//  SAHIPLIK: kurallar unique_ptr icinde tutulur, yani bu sinif
//  onlarin tek sahibidir. Eskiden ham pointer tutuluyor ve
//  destructor'da elle delete ediliyordu; simdi silme isini
//  unique_ptr'in kendisi yapiyor.
//
//  Bu yuzden bu sinifta ARTIK destructor, kopya constructor ve
//  kopya atama YOK — unique_ptr kopyalanamadigi icin derleyici
//  kopya islemlerini zaten siliyor, vector yok olurken de
//  kurallar temizleniyor. Buna Rule of Zero denir: kaynak
//  yonetimini kendi kaynagini yoneten tiplere devredersen,
//  sinifin bu ozel fonksiyonlarindan hicbirini yazmazsin.
// ============================================================
class AlarmDegerlendirici
{
public:
    // Parametre DEGERLE aliniyor: cagiran std::move ile sahipligi
    // devretmek zorunda, yani imza "buranin sahibi artik benim" diyor.
    void kuralEkle(std::unique_ptr<AlarmKurali> kural);

    bool degerlendir(const Olcumler &o, QString &mesajOut) const;

    void kurallariTemizle();

private:
    // QList degil std::vector: tasinabilir-ama-kopyalanamaz tipleri
    // (unique_ptr gibi) sorunsuz tasir.
    std::vector<std::unique_ptr<AlarmKurali>> kurallar;
};

#endif // ALARMDEGERLENDIRICI_H
