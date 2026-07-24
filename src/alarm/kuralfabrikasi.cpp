#include "kuralfabrikasi.h"

QList<AlarmKurali *> KuralFabrikasi::olustur(HastaTipi tip)
{
    QList<AlarmKurali *> liste;

    liste.append(new DusukOksijenKurali(90));
    liste.append(new YuksekEtco2Kurali(47));

    switch (tip) {
    case HastaTipi::Bebek:
        liste.append(new TakipneKurali(60));
        break;
    case HastaTipi::Cocuk:
        liste.append(new TakipneKurali(35));
        break;                     // BU break EKSİKTİ → fall-through ile Eriskin'e
                                   // düşüyor, çocuğa 35 VE 25 kuralı birden
                                   // ekleniyordu. Değerlendirici ilk tetikleneni
                                   // döndürdüğü için çocuk 25'te alarm veriyordu.
    case HastaTipi::Eriskin:
        liste.append(new TakipneKurali(25));
        break;

    }
    return liste;
}
