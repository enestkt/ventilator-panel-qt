#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // --- Global açık monitör teması ---
    a.setStyleSheet(R"(
        /* Zemin rengini SADECE pencereye veriyoruz.
           Onceden bu kural "QWidget" idi ve istisnasiz her widget'a
           arka plan boyuyordu; bir QGroupBox'i duz QWidget'a
           donusturdugumuz anda o widget sayfa grisiyle boyanip
           icinde bulundugu acik gri grubun uzerinde kutu gibi
           gorunuyordu. Zemin pencerede, yazi rengi ve font ise
           kalitim yoluyla tum widget'lara iniyor. */
        QMainWindow {
            background-color: #eef1f4;
        }
        QWidget {
            color: #1c2733;
            font-size: 13px;
        }
        QGroupBox {
            border: 1px solid #c3ccd6;
            border-radius: 8px;
            margin-top: 10px;
            padding-top: 6px;
            font-weight: bold;
            background-color: #f7f9fb;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 10px;
            color: #5b6b7b;
        }
        QPushButton {
            background-color: #ffffff;
            border: 1px solid #c3ccd6;
            border-radius: 6px;
            padding: 8px 16px;
            color: #1c2733;
        }
        QPushButton:hover  { background-color: #e3e9ef; }
        QPushButton:pressed{ background-color: #d2dae2; }
        QPushButton:checked{ background-color: #cfe3f7; border: 2px solid #4a90d9;
                             font-weight: bold; }
        QListWidget {
            background-color: #ffffff;
            border: 1px solid #c3ccd6;
            border-radius: 6px;
        }

        /* --- QSlider ---
           Global bir stylesheet devreye girdiginde Qt, cizimi
           QStyleSheetStyle'a devreder. Kural yazilmayan alt parcalar
           (groove, handle, sub-page) platform stilinin yerine geri
           donus cizimiyle olusur ve temaya uymayabilir. Slider bu
           yuzden panelin disinda duruyordu; parcalarini acikca
           tanimliyoruz. */
        QSlider::groove:horizontal {
            height: 6px;
            border-radius: 3px;
            background: #dbe2ea;      /* yay gostergesinin gri izi ile ayni */
        }
        QSlider::sub-page:horizontal {
            height: 6px;
            border-radius: 3px;
            background: #4a90d9;      /* secili buton cercevesiyle ayni mavi */
        }
        QSlider::handle:horizontal {
            width: 16px;
            margin: -6px 0;           /* groove'dan tasarak yuvarlak gorunur */
            border-radius: 9px;
            background: #ffffff;
            border: 2px solid #4a90d9;
        }
        QSlider::handle:horizontal:hover {
            background: #e8f1fb;
        }
    )");

    MainWindow w;
    w.show();
    return QApplication::exec();
}
