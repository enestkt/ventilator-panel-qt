#include "alarmdegerlendirici.h"

#include <utility>   // std::move

void AlarmDegerlendirici::kurallariTemizle()
{
    // Eskiden burada dongu ile tek tek delete ediliyordu.
    // clear() vector'u bosaltirken icindeki unique_ptr'lar yok olur,
    // onlar da isaret ettikleri kurallari siler.
    kurallar.clear();
}

void AlarmDegerlendirici::kuralEkle(std::unique_ptr<AlarmKurali> kural)
{
    if (kural)
        kurallar.push_back(std::move(kural));
}

bool AlarmDegerlendirici::degerlendir(const Olcumler &o, QString &mesajOut) const
{
    // const auto & : unique_ptr kopyalanamaz, degerle alsaydik derlenmezdi.
    for (const auto &kural : kurallar) {
        if (kural->tetiklendiMi(o)) {     // POLIMORFIZM — vtable uzerinden
            mesajOut = kural->mesaj();
            return true;
        }
    }

    mesajOut.clear();
    return false;
}
