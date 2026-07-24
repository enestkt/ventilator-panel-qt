#ifndef KURALFABRIKASI_H
#define KURALFABRIKASI_H

#include "alarmkurali.h"
#include "hastatipi.h"
#include <QList>

class KuralFabrikasi
{
public:
    static QList<AlarmKurali *> olustur(HastaTipi tip);
};

#endif // KURALFABRIKASI_H
