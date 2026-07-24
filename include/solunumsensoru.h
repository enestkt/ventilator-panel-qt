#ifndef SOLUNUMSENSORU_H
#define SOLUNUMSENSORU_H

#include <QTimer>
#include <iolcumkaynagi.h>
#include "alarmdegerlendirici.h"
#include "hastatipi.h"


class SolunumSensoru : public IOlcumKaynagi
{
    Q_OBJECT

public:
    explicit SolunumSensoru (QObject *parent=nullptr);

    void basla() override;
    void durdur() override;
    bool calisiyorMu() const override;
    void hiziAyarla(int yeniHiz);
    void istatistikSifirla();
    void hastaTipiAyarla(HastaTipi tip);

signals:
    void istatistiklerGuncellendi(int enDusuk, int enYuksek);

private slots:
    void olcumYap();

private:
    void alarmiKontrolEt();
    QTimer *timer;
    int mevcutHiz;
    int mevcutSpo2;
    bool sonAlarmAktif;
    QString sonAlarmMesaj;
    int mevcutVt;
    int mevcutEtco2;
    int enDusukHiz;
    int enYuksekHiz;
    AlarmDegerlendirici degerlendirici;
};

#endif
