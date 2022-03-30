#include "ShowNotice.h"
#include "ui_ShowNotice.h"

CShowNotice::CShowNotice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CShowNotice)
{
    ui->setupUi(this);

}

CShowNotice::~CShowNotice()
{
    delete ui;
}

/// 设置显示信息
void CShowNotice::SetShowInfo(const QString &sInfo)
{
    if(this->isHidden())
    {
        this->show();
    }

    ui->plainTextEdit->insertPlainText(sInfo+"\n");
}

void CShowNotice::ClearInfo()
{
    ui->plainTextEdit->clear();
}
