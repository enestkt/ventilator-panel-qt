#ifndef SOLUNUMDALGASI_H
#define SOLUNUMDALGASI_H

#include <QWidget>
#include <QList>
#include <QTimer>
#include "cizimwidget.h"

class SolunumDalgasi : public CizimWidget
{
    Q_OBJECT
public:
    explicit SolunumDalgasi(QWidget *parent = nullptr);

public slots:
    void hiziAyarla(int nefesDakika);

protected:
    void iceriCiz(QPainter &boya) override;

private slots:
    void ilerle();

private:
    QTimer *animTimer;
    double faz;
    int solunumHizi;
    QList<double> ornekler;

};
#endif // SOLUNUMDALGASI_H
