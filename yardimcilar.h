#ifndef YARDIMCILAR_H
#define YARDIMCILAR_H

// ============================================================
//  Yardımcı fonksiyonlar — C++ parametre geçirme yöntemleri
//  ve inline fonksiyon gösterimi
// ============================================================

// ---- INLINE FONKSİYON + CALL BY VALUE ----
// inline: fonksiyonun GÖVDESİ header'da. Bu header'ı birden çok .cpp
//   include etse bile "çift tanım" (multiple definition) hatası olmaz —
//   inline'ın header'daki asıl görevi budur.
// call by value: deger/alt/ust birer KOPYA olarak gelir. Fonksiyon
//   içinde değiştirsek bile çağıran taraftaki asıl değişken etkilenmez.
inline int araliktaTut(int deger, int alt, int ust)
{
    if (deger < alt) return alt;
    if (deger > ust) return ust;
    return deger;
}

// ---- CALL BY REFERENCE ----
// min ve max, REFERANS (&) ile geliyor: bunlar çağıranın değişkenlerinin
// kendisidir (kopya değil, takma ad). Fonksiyon onları DOĞRUDAN değiştirir;
// değer döndürmeye gerek kalmaz.
void minMaxGuncelle(int deger, int &min, int &max);

// ---- CALL BY POINTER ----
// sonuc bir İŞARETÇİ (*): bir ADRES geliyor. Pointer null olabileceği için
// önce kontrol ederiz; sonucu *sonuc = ... ile o adrese yazarız.
bool etco2KPaHesapla(int mmHg, double *sonuc);

#endif // YARDIMCILAR_H
