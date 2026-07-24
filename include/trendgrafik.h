#ifndef TRENDGRAFIK_H
#define TRENDGRAFIK_H

#include <QWidget>
#include <QList>
#include "cizimwidget.h"

class TrendGrafik : public CizimWidget
{
    Q_OBJECT
public:
    explicit TrendGrafik(QWidget *parent = nullptr);

public slots:
    void degerEkle(int deger);

protected:
    void iceriCiz(QPainter &boya) override;

private:
    int yKoordinati(int deger) const;
    QList<int> degerler;
};

#endif // TRENDGRAFIK_H
