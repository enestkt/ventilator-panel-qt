#include "yardimcilar.h"

// ---- CALL BY REFERENCE ----
// min ve max referans olduğu için, buradaki atamalar doğrudan
// çağıran fonksiyondaki değişkenleri değiştirir.
void minMaxGuncelle(int deger, int &min, int &max)
{
    if (deger < min) min = deger;
    if (deger > max) max = deger;
}

// ---- CALL BY POINTER ----
// sonuc bir adres; önce null mı diye korunur, sonra o adrese yazılır.
bool etco2KPaHesapla(int mmHg, double *sonuc)
{
    if (sonuc == nullptr)          // pointer null olabilir → önce koru
        return false;
    *sonuc = mmHg * 0.133322;      // mmHg → kPa dönüşümü, adrese yaz
    return true;
}
