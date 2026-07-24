#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTime>
#include "yardimcilar.h"
#include "arcgosterge.h"
#include "solunumsensoru.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(std::make_unique<Ui::MainWindow>())
{
    ui->setupUi(this);

    // Not: layout stretch degerleri artik .ui dosyasinda (layoutStretch
    // ozelligi) tanimli. Eskiden burada koddan veriliyordu; ayni ayarin
    // iki yerde durmamasi icin buradan kaldirildi.

    // --- Yay göstergelerini tanımla (aralık + birim + başlangıç) ---
    ui->hizGauge->ayarla(5, 40, "/dk");      ui->hizGauge->degeriAyarla(12);
    ui->spo2Gauge->ayarla(70, 100, "%");     ui->spo2Gauge->degeriAyarla(98);
    ui->vtGauge->ayarla(350, 550, "mL");     ui->vtGauge->degeriAyarla(450);
    ui->fio2Gauge->ayarla(21, 100, "%");     ui->fio2Gauge->degeriAyarla(40);
    ui->peepGauge->ayarla(0, 20, "cmH2O");   ui->peepGauge->degeriAyarla(5);
    ui->etco2Gauge->ayarla(30, 50, "mmHg");  ui->etco2Gauge->degeriAyarla(38);

    SolunumSensoru *sim = new SolunumSensoru(this);
    kaynak = sim;

    connect(kaynak, &IOlcumKaynagi::hizGuncellendi,
            ui->hizGauge, &ArcGosterge::degeriAyarla);
    connect(kaynak, &IOlcumKaynagi::spo2Guncellendi,
            ui->spo2Gauge, &ArcGosterge::degeriAyarla);
    connect(kaynak, &IOlcumKaynagi::vtGuncellendi,
            ui->vtGauge, &ArcGosterge::degeriAyarla);
    connect(kaynak, &IOlcumKaynagi::hizGuncellendi,
            ui->trendGrafik, &TrendGrafik::degerEkle);
    connect(kaynak, &IOlcumKaynagi::hizGuncellendi,
            ui->solunumDalgasi, &SolunumDalgasi::hiziAyarla);
    connect(kaynak, &IOlcumKaynagi::alarmDurumu,
            this, &MainWindow::alarmGoster);
    connect(kaynak, &IOlcumKaynagi::alarmDurumu,
            this, &MainWindow::alarmKaydet);

    connect(kaynak, &IOlcumKaynagi::etco2Guncellendi,
            this, [this](int deger){
        ui->etco2Gauge->degeriAyarla(deger);
        double kpa = 0.0;
        etco2KPaHesapla(deger, &kpa);
        ui->etco2Gauge->setToolTip(QString("%1 kPa").arg(kpa, 0, 'f', 1));
    });

    // --- Sadece simülasyonda anlamlı olanlar (arayüzde YOK — somut tip üzerinden) ---
    connect(ui->hizSlider, &QSlider::valueChanged,
            sim, &SolunumSensoru::hiziAyarla);

    connect(sim, &SolunumSensoru::istatistiklerGuncellendi,
            this, [this](int enDusuk, int enYuksek){
        ui->istatistikLabel->setText(
            QString("En düşük: %1   En yüksek: %2").arg(enDusuk).arg(enYuksek));
    });

    connect(ui->resetButton, &QPushButton::clicked,
            sim, [sim](){ sim->istatistikSifirla(); });

    connect(ui->baslatDurdurButton, &QPushButton::clicked,
            this, &MainWindow::baslatDurdurBasildi);


    auto hastaTipiSec = [this, sim](HastaTipi tip, const QString &ad){
        sim->hastaTipiAyarla(tip);
        ui->alarmListesi->addItem(
            QTime::currentTime().toString("hh:mm:ss") + " Hasta tipi: " + ad);
        ui->alarmListesi->scrollToBottom();
    };
    connect(ui->eriskinButton, &QPushButton::clicked, sim,
            [hastaTipiSec](){ hastaTipiSec(HastaTipi::Eriskin, "Erişkin"); });
    connect(ui->bebekButton, &QPushButton::clicked,sim,
            [hastaTipiSec](){ hastaTipiSec(HastaTipi::Bebek, "Bebek");});
    connect(ui->cocukButton, &QPushButton::clicked, sim,
            [hastaTipiSec](){ hastaTipiSec(HastaTipi::Cocuk, "Çocuk");});

    kaynak->basla();

    alarmGoster(false, "");   // başlangıçta "Durum: Normal" stilini uygula
}



void MainWindow::baslatDurdurBasildi()
{
    if (kaynak->calisiyorMu()) {
        kaynak->durdur();
        ui->baslatDurdurButton->setText("Başlat");
    } else {
        kaynak->basla();
        ui->baslatDurdurButton->setText("Durdur");
    }
}


void MainWindow::alarmGoster(bool aktif, const QString &mesaj)
{
    if(aktif){
        ui->alarmLabel->setText("🔔  " + mesaj);
        ui->alarmLabel->setAlignment(Qt::AlignCenter);
        ui->alarmLabel->setStyleSheet(
            "background-color: #d32f2f; color: white; font-weight: bold;"
            "padding: 10px; border-radius: 6px;");
    }else{
        ui->alarmLabel->setText("Durum: Normal");
        ui->alarmLabel->setAlignment(Qt::AlignCenter);
        ui->alarmLabel->setStyleSheet(
            "background-color: #e6f4ea; color: #1e7e34; font-weight: bold;"
            "padding: 10px; border-radius: 6px;");
    }
}

void MainWindow::alarmKaydet(bool aktif, const QString &mesaj)
{
    QString zaman = QTime::currentTime().toString("hh:mm:ss");

    if(aktif)
        ui->alarmListesi->addItem(zaman + "  🚨 " + mesaj);
    else
        ui->alarmListesi->addItem(zaman + "✅ Normale döndü");

    ui->alarmListesi->scrollToBottom();

}

// Govdesi bos ama .cpp'de tanimlanmak ZORUNDA: ui bir
// unique_ptr<Ui::MainWindow> ve Ui::MainWindow header'da sadece
// ileri bildirilmis. unique_ptr yikim aninda tipin tam tanimini
// gerektirir; o tanim ancak burada, ui_mainwindow.h include
// edildikten sonra gorunur.
MainWindow::~MainWindow() = default;

