    #ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    Ui::MainWindow *ui;
    IOlcumKaynagi *kaynak;
};
#endif // MAINWINDOW_H
