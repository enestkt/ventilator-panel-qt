#include "kuralfabrikasi.h"

std::vector<std::unique_ptr<AlarmKurali>> KuralFabrikasi::olustur(HastaTipi tip)
{
    std::vector<std::unique_ptr<AlarmKurali>> liste;

    // make_unique, new'in yerini alir: nesneyi kurar ve sahipligi
    // dogrudan bir unique_ptr icine koyar. Arada sahipsiz kalan
    // ham pointer olusmaz.
    liste.push_back(std::make_unique<DusukOksijenKurali>(90));
    liste.push_back(std::make_unique<YuksekEtco2Kurali>(47));

    // Takipne esigi hasta tipine gore degisir.
    // switch'e bilincli olarak default KOYULMADI: yeni bir HastaTipi
    // eklenirse derleyici "enumeration value not handled" uyarisi versin.
    switch (tip) {
    case HastaTipi::Bebek:
        liste.push_back(std::make_unique<TakipneKurali>(60));
        break;
    case HastaTipi::Cocuk:
        liste.push_back(std::make_unique<TakipneKurali>(35));
        break;
    case HastaTipi::Eriskin:
        liste.push_back(std::make_unique<TakipneKurali>(25));
        break;
    }

    return liste;
}
