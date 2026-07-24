#include "solunumsensoru.h"
#include <QRandomGenerator>
#include <utility>          // std::move
#include "yardimcilar.h"
#include "kuralfabrikasi.h"

    SolunumSensoru::SolunumSensoru(QObject *parent)
        :IOlcumKaynagi(parent)
        , timer(new QTimer(this))
        , mevcutHiz(12)
        , mevcutSpo2(98)
        , sonAlarmAktif(false)
        , mevcutVt(450)
        , mevcutEtco2(38)
        , enDusukHiz(12)
        , enYuksekHiz(12)
    {
        connect(timer, &QTimer::timeout, this, &SolunumSensoru::olcumYap);
        hastaTipiAyarla(HastaTipi::Eriskin);
    }

    void SolunumSensoru::hastaTipiAyarla(HastaTipi tip)
    {
        degerlendirici.kurallariTemizle();

        // Fabrika sahipligi bize devrediyor, biz de std::move ile
        // degerlendiriciye devrediyoruz. Sahiplik zinciri her adimda
        // tek elde kaliyor.
        for (auto &kural : KuralFabrikasi::olustur(tip))
            degerlendirici.kuralEkle(std::move(kural));

        alarmiKontrolEt();
    }
    void SolunumSensoru::basla()
    {
        timer->start(1000);
    }
    void SolunumSensoru::olcumYap()
    {
        mevcutHiz += QRandomGenerator::global()->bounded(-2,3);
        mevcutHiz = araliktaTut(mevcutHiz, 5, 40);
        emit hizGuncellendi(mevcutHiz);

        minMaxGuncelle(mevcutHiz, enDusukHiz, enYuksekHiz);
        emit istatistiklerGuncellendi(enDusukHiz, enYuksekHiz);

       mevcutSpo2 += QRandomGenerator::global()->bounded(-1, 2);
       mevcutSpo2 = araliktaTut(mevcutSpo2, 85, 100);
       emit spo2Guncellendi(mevcutSpo2);

       mevcutVt += QRandomGenerator::global()->bounded(-15, 16);
       mevcutVt = araliktaTut(mevcutVt, 350, 550);
       emit vtGuncellendi(mevcutVt);

       mevcutEtco2 += QRandomGenerator::global()->bounded(-1, 2);
       mevcutEtco2 = araliktaTut(mevcutEtco2, 30, 50);
       emit etco2Guncellendi(mevcutEtco2);

        alarmiKontrolEt();
    }
    void SolunumSensoru::durdur(){
        timer->stop();
    }
    bool SolunumSensoru::calisiyorMu() const{
        return timer->isActive();
    }

    void SolunumSensoru::hiziAyarla(int yeniHiz){
        mevcutHiz = yeniHiz;
        emit hizGuncellendi(mevcutHiz);
        alarmiKontrolEt();
    }

    void SolunumSensoru::alarmiKontrolEt()
    {
        Olcumler o;
        o.hiz = mevcutHiz;
        o.spo2 = mevcutSpo2;
        o.etco2 = mevcutEtco2;
        o.vt = mevcutVt;

        QString mesaj;
        bool aktif = degerlendirici.degerlendir(o, mesaj);

        if(aktif !=sonAlarmAktif || mesaj != sonAlarmMesaj){
            sonAlarmAktif = aktif;
            sonAlarmMesaj = mesaj;
            emit alarmDurumu(aktif, mesaj);
        }
    }


void SolunumSensoru::istatistikSifirla()
    {
    enDusukHiz = mevcutHiz;
    enYuksekHiz = mevcutHiz;
    emit istatistiklerGuncellendi(enDusukHiz, enYuksekHiz);
    }
