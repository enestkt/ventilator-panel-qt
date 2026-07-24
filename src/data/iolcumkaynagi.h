#ifndef IOLCUMKAYNAGI_H
#define IOLCUMKAYNAGI_H

#include <QObject>
#include <QString>

class IOlcumKaynagi : public QObject
{
    Q_OBJECT
public:
    explicit IOlcumKaynagi(QObject *parent = nullptr) : QObject(parent){}
    ~IOlcumKaynagi() override = default;

    virtual void basla() = 0;
    virtual void durdur() = 0;
    virtual bool calisiyorMu() const = 0;

signals:
    void hizGuncellendi(int yeniHiz);
    void spo2Guncellendi(int yeniSpo2);
    void vtGuncellendi(int yeniVt);
    void etco2Guncellendi(int yeniEtco2);
    void alarmDurumu(bool aktif, const QString &mesaj);
};

#endif // IOLCUMKAYNAGI_H
