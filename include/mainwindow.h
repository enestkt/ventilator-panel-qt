    #ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include "iolcumkaynagi.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void baslatDurdurBasildi();
    void alarmGoster(bool aktif, const QString &mesaj);
    void alarmKaydet(bool aktif, const QString &mesaj);

private:
    // SAHIP: formu biz kuruyoruz, biz yok ediyoruz → unique_ptr.
    std::unique_ptr<Ui::MainWindow> ui;

    // SAHIP DEGIL: kaynagin sahibi Qt'nin parent-child zinciri
    // (new SolunumSensoru(this)). Buradaki pointer sadece "bakiyor".
    // Sahiplenmeyen bir pointer icin ham pointer DOGRU aractir;
    // unique_ptr'a sarmak yanlis bir mesaj verir ve cift silme yaratir.
    IOlcumKaynagi *kaynak;
};
#endif // MAINWINDOW_H
