#include "solunumdalgasi.h"
#include "QPainter"
#include "QtMath"

SolunumDalgasi::SolunumDalgasi(QWidget *parent)
    : CizimWidget(parent)
    , animTimer(new QTimer(this))
    , faz(0.0)
    , solunumHizi(12)
    {

    zeminRengi = QColor(10,15,25);
    setMinimumHeight(45);
    connect(animTimer, &QTimer::timeout, this, &SolunumDalgasi::ilerle);
    animTimer->start(30);

    }
    void SolunumDalgasi::hiziAyarla(int nefesDakika)
    {
        solunumHizi=nefesDakika;
    }

    void SolunumDalgasi::ilerle()
    {
        faz+=solunumHizi * 0.004;

        double yeniOrnek=qSin(faz);
        ornekler.append(yeniOrnek);

        while(ornekler.size() >200)
            ornekler.removeFirst();

            update();
    }
    void SolunumDalgasi::iceriCiz(QPainter &boya)
    {
        boya.setPen(QPen(QColor(40,55,70), 1));
        boya.drawLine(0, height() / 2, width(), height() / 2);

        if(ornekler.size() < 2)
            return;

        boya.setPen(QPen(QColor(0,230,255) ,2));
        double xAdim = double(width()) / 199.0;

        for (int i = 1; i < ornekler.size(); ++i) {
            int x1 = int((i - 1) * xAdim);
            int y1 = height() / 2 - int (ornekler[i-1] * height() /2 * 0.8);
            int x2 = int(i*xAdim);
            int y2 = height() / 2 - int(ornekler[i] * height() / 2 * 0.8);
            boya.drawLine(x1,y1,x2,y2);

        }

    }
