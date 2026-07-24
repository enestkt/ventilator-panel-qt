#include "alarmdegerlendirici.h"

AlarmDegerlendirici::~AlarmDegerlendirici()
{
    kurallariTemizle();
}

void AlarmDegerlendirici::kurallariTemizle()
{
    for(AlarmKurali *kural : kurallar)
        delete kural;
    kurallar.clear();
}
void AlarmDegerlendirici::kuralEkle(AlarmKurali *kural)
{
    if(kural)
        kurallar.append(kural);
}

bool AlarmDegerlendirici::degerlendir(const Olcumler &o, QString &mesajOut) const
{
    for (AlarmKurali *kural : kurallar){
        if(kural->tetiklendiMi(o)){
            mesajOut = kural->mesaj();
            return true;
        }
    }
    mesajOut.clear();
    return false;
}

