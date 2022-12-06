#include "NoticInfo.h"

NoticInfo::NoticInfo(QObject *parent)
    : QObject{parent}
{

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
