#ifndef CIZIMWIDGET_H
#define CIZIMWIDGET_H

#include <QWidget>
#include <QPainter>

// ============================================================
//  CizimWidget — ORTAK TABAN SINIF (abstract / soyut)
//  TrendGrafik ve SolunumDalgasi bundan TÜRER (inheritance).
//  Zemini kendisi çizer; asıl içeriği alt sınıflara bırakır.
// ============================================================
class CizimWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CizimWidget(QWidget *parent = nullptr);

protected:
    // ORTAK: zemini çizer, sonra iceriCiz()'i çağırır. (şablon metot)
    void paintEvent(QPaintEvent *event) override;

    // SAF SANAL (= 0): gövdesi YOK. Her alt sınıf bunu yazmak ZORUNDA.
    // Bu satır yüzünden CizimWidget "soyut" olur — tek başına nesnesi yaratılamaz.
    virtual void iceriCiz(QPainter &boya) = 0;

    // ortak zemin rengi — alt sınıf isterse değiştirebilir (protected → çocuğa açık)
    QColor zeminRengi = QColor(15, 25, 35);
};

#endif // CIZIMWIDGET_H
