#ifndef ALARMDEGERLENDIRICI_H
#define ALARMDEGERLENDIRICI_H

#include "alarmkurali.h"
#include <QList>

class AlarmDegerlendirici
{
public:
    AlarmDegerlendirici() = default;
    ~AlarmDegerlendirici();

    AlarmDegerlendirici(const AlarmDegerlendirici &) = delete;
    AlarmDegerlendirici &operator=(const AlarmDegerlendirici &) = delete;

    void kuralEkle(AlarmKurali *kural);

    bool degerlendir (const Olcumler &o, QString &mesajOut) const;

    void kurallariTemizle();

private:
    QList<AlarmKurali *> kurallar;
};

#endif // ALARMDEGERLENDIRICI_H
