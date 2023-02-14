#include "NoticInfo.h"


NoticInfo::NoticInfo(QObject *parent)
    : QObject{parent}
{
}

void NoticInfo::setNoticNum(int NoiceNum)
{
    m_nNoticNum=NoiceNum;
}

void NoticInfo::setNoiceText(const QString& sNoice)
{
    if(sNoice != m_sNoticText)
    {
        m_sNoticText = sNoice;
        emit noticTextChanged();
    }
}

void NoticInfo::setColorNotic(const QColor &rColor)
{
    if(rColor !=m_colorNotic )
    {
        m_colorNotic = rColor;
        emit colorNoticChanged();
    }
}

void NoticInfo::writeNoiceText(QJsonObject &rObj)
{
    rObj["NUM"] = m_nNoticNum;
    rObj["NoticText"] = m_sNoticText;
}

void NoticInfo::readNoiceText(const QJsonObject &rObj)
{
    if (rObj.contains("NUM") && rObj["NUM"].isDouble())
        m_nNoticNum = rObj["NUM"].toInt();

    if (rObj.contains("NoticText") && rObj["NoticText"].isString())
        m_sNoticText = rObj["NoticText"].toString();

}

