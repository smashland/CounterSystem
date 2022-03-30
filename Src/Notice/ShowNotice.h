#ifndef SHOWNOTICE_H
#define SHOWNOTICE_H

#include <QDialog>
//#include <QPropertyAnimation>
namespace Ui {
class CShowNotice;
}


class CShowNotice : public QDialog
{
    Q_OBJECT

public:
    explicit CShowNotice(QWidget *parent = 0);
    ~CShowNotice();

    void SetShowInfo(const QString& sInfo);
    void ClearInfo();

private:
    Ui::CShowNotice *ui;
//    QPropertyAnimation* m_pAnimation;
};

#endif // SHOWNOTICE_H
