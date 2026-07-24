#ifndef KURALFABRIKASI_H
#define KURALFABRIKASI_H

#include "alarmkurali.h"
#include "hastatipi.h"
#include <memory>
#include <vector>

// ============================================================
//  KuralFabrikasi — hasta tipine gore alarm kurali seti uretir.
//
//  Donus tipi unique_ptr vektoru: fonksiyon sadece nesneleri degil
//  SAHIPLIKLERINI de dondurur. Eskiden QList<AlarmKurali*> donuyordu
//  ve "bunlari kim silecek?" sorusunun cevabi imzada gorunmuyordu.
// ============================================================
class KuralFabrikasi
{
public:
    static std::vector<std::unique_ptr<AlarmKurali>> olustur(HastaTipi tip);
};

#endif // KURALFABRIKASI_H
